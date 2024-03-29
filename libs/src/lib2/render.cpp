//
// Created by Andromaleus on 2017-06-08.
//

#include "lib2.h"

featured_renderer *renderer;
sf::Font font;

//sf::RenderWindow window(sf::VideoMode(640, 480), "Nibbler");
//sf::Texture texture;
//sf::Texture advanced_texture[3];
//int bodyswivel = 2;//to swivel in one direction
//    std::clock_t    time = std::clock();

void         initialize(renderData rdata)
{
    featured_renderer *new_renderer = new featured_renderer();

    if (!font.loadFromFile("textures/lib2/fonts/Capture_it.ttf"))
    {
        std::cout << "error" << std::endl;
        exit(EXIT_FAILURE);
        // error...
    }
    renderer = new_renderer;
}

void          clean()
{
    delete renderer;
}

renderData    simple_rendering(renderData rdata)
{
    static float        n[2];
    int                 x = 0;
    int                 xrenderdir = rdata.playerXDirection;//1 * (rdata.playerBody[x - 1][0]);
    int                 yrenderdir = rdata.playerYDirection;

    sf::CircleShape     shape(rdata.objWidth / 2);//original
    sf::Sprite          background;
    sf::Sprite          rfood;//fd
    sf::Sprite          main_background;//scorebox
    sf::Sprite          snake_skull;//snake_skull
    sf::RectangleShape  score_box(sf::Vector2f(rdata.winWidth * rdata.objWidth, rdata.winHeight * rdata.objHeight));


    if (n[0] > 0.05 || n[0] < -0.05)
        renderer->setbackground_movement_direction(-renderer->getbackground_movement_direction());
    if (!(n[0] > 2.0f && !(n[0] = 0)))
        n[0] += 0.001 * static_cast<float>(renderer->getbackground_movement_direction());//
    renderer->setbodyswivel(-renderer->getbodyswivel());
    rfood.setTexture(renderer->getfood_textures()[renderer->getfood()]);//changes int here.
    rfood.setScale(0.09f, 0.09f);

    snake_skull.setTexture(renderer->getsnake_head_textures()[renderer->getsnake_head()]);//semi-constant
    snake_skull.setScale(sf::Vector2f(0.05f, 0.05f));//constant
    snake_skull.rotate(-90 * (rdata.playerXDirection != 0));

    background.setTexture(renderer->getbg_textures()[renderer->getbackground()]);//semi-const
    background.setScale(sf::Vector2f(0.5f + n[0] * 0.75, 0.5f + n[0] * 0.75));//constant
    background.rotate(n[0] * 10);

    main_background.setTexture(renderer->getbg_textures()[renderer->getbackground()]);//is not yet fully calculated.
    main_background.setColor(sf::Color(200.0, 200.0, 200.0, 255 * 0.8f));
    main_background.move(rdata.winWidth - 160, 0);//to change-up.(CURRENTLY HARDCODED).

    renderer->getwindow()->clear();
    renderer->getwindow()->draw(background);//texture
    renderer->getwindow()->draw(main_background);

    snake_skull.move(rdata.playerPosX * rdata.objWidth - rdata.objWidth / 3, rdata.playerPosY * rdata.objHeight - (rdata.objHeight / 2) + rdata.objHeight * 1.9 * (rdata.playerXDirection != 0));
    renderer->getwindow()->draw(snake_skull);
    for (int i = 1; i <= rdata.playerBody.size(); i++)
    {
        sf::Sprite          snake_body;
        sf::CircleShape     bodyshape(rdata.objWidth / 2);

        x > 0 && (xrenderdir = -(rdata.playerBody[x - 1][0] < rdata.playerBody[x][0]) + (rdata.playerBody[x - 1][0] > rdata.playerBody[x][0]));
        int                 xswivel = ((i % 3 == 0) ? -renderer->getbodyswivel() : renderer->getbodyswivel()) * (!xrenderdir);//rdata.playerXDirection);
        int                 yswivel = ((i % 3 == 0) ? -renderer->getbodyswivel() : renderer->getbodyswivel()) * (!yrenderdir);//rdata.playerYDirection);

        snake_body.setTexture(renderer->getsnake_textures()[0]);
        snake_body.setScale(sf::Vector2f(0.05f, 0.05f));
        snake_body.rotate(-90 * (xrenderdir != 0));//-180 * (rdata.playerYDirection == 1));
        snake_body.move((rdata.playerBody[x][0]) * rdata.objWidth - rdata.objWidth / 3 + xswivel, (rdata.playerBody[x][1]) * rdata.objHeight - (rdata.objHeight / 2) + rdata.objHeight * 1.9 * (xrenderdir != 0) + yswivel);
        renderer->getwindow()->draw(snake_body);
        ++x;
    }

    rfood.move((rdata.foodPosX) * rdata.objWidth, rdata.foodPosY * rdata.objHeight);
    renderer->getwindow()->draw(rfood);

    score_box.setFillColor(sf::Color(15, 15, 15, 128));
    score_box.move(rdata.winWidth * rdata.objWidth, 0);
    renderer->getwindow()->draw(score_box);


    sf::Text text;

    text.setFont(font); // font is a sf::Font
    text.setString("SCORE: " + std::to_string(rdata.score));
    text.setCharacterSize(17); // in pixels, not points!
    text.move(rdata.winWidth * rdata.objWidth + rdata.objWidth, 0);
//    text.setColor(sf::Color(15, 15, 15, 128));
//    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    renderer->getwindow()->draw(text);
    return (rdata);
}

renderData     render(renderData rdata)
{
    sf::Event           event;

    if (!renderer->getwindow()->isOpen())
        exit(EXIT_FAILURE);//if window gets abrupty closed(to change the way it exits).
    rdata = simple_rendering(rdata);
    renderer->getwindow()->display();
    while (renderer->getwindow()->pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                renderer->getwindow()->close();//to review decision.
                exit(EXIT_FAILURE);
                break;
            case sf::Event::KeyPressed:
            {

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
                    rdata.key = 1;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
                    rdata.key = 3;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    std::cout << "left\n";
                    if (rdata.playerXDirection != 1 && !rdata.dir)
                    {
                        rdata.playerXDirection = -1;
                        rdata.playerYDirection = 0;
                        rdata.dir = true;
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    if (rdata.playerXDirection != -1 && !rdata.dir)
                    {
                        rdata.playerXDirection = 1;
                        rdata.playerYDirection = 0;
                        rdata.dir = true;
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    std::cout << "up\n";
                    if (rdata.playerYDirection != 1 && !rdata.dir)
                    {
                        rdata.playerXDirection = 0;
                        rdata.playerYDirection = -1;
                        rdata.dir = true;
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    std::cout << "down\n";
                    if (rdata.playerYDirection != -1 && !rdata.dir)
                    {
                        rdata.playerXDirection = 0;
                        rdata.playerYDirection = 1;
                        rdata.dir = true;
                    }
                }
            }
        }
    }
    std::cout << "lib2 running" << rdata.key << std::endl;
    return (rdata);
}