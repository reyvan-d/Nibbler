//
// Created by Andromaleus on 2017-06-08.
//

#include "lib3.h"

renderData glData;

void initialize(renderData rdata)
{
    glutInit(&rdata.ac, rdata.av);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640, 640);
    glutCreateWindow("Nibbler");
    glutDisplayFunc(&renderScreen);
    glutKeyboardFunc(handleKeypress);
    glutSpecialFunc(specialInput);
    glutReshapeFunc(handleResize);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
    glewInit();
    if (!GLEW_VERSION_3_3)
    {
        std::cerr << "OpenGL 3.3 not available" << std::endl;
        exit(1);
    }
    glEnable(GL_DEPTH_TEST);
    return ;
}

void specialInput(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_UP:
            if (glData.playerYDirection != 1 && !glData.dir)
            {
                glData.playerYDirection = -1;
                glData.playerXDirection = 0;
                glData.dir = true;
                break;
            }
        case GLUT_KEY_DOWN:
            if (glData.playerYDirection != -1 && !glData.dir)
            {
                glData.playerYDirection = 1;
                glData.playerXDirection = 0;
                glData.dir = true;
                break;
            }
        case GLUT_KEY_LEFT:
            if (glData.playerXDirection != 1 && !glData.dir)
            {
                glData.playerXDirection = -1;
                glData.playerYDirection = 0;
                glData.dir = true;
                break;
            }
        case GLUT_KEY_RIGHT:
            if (glData.playerXDirection != -1 && !glData.dir)
            {
                glData.playerXDirection = 1;
                glData.playerYDirection = 0;
                glData.dir = true;
                break;
            }
    }
}

void handleResize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPerspective(45.0, static_cast<double>(w) / static_cast<double>(h), 1.0, 200.0);
}

void handleKeypress(unsigned char key, int x, int y)
{
    std::cout << key << std::endl;
    switch(key)
    {
        case '1':
            glData.key = 1;
            break;
        case '2':
            glData.key = 2;
            break;
        case 27:
            exit(0);
    }
}

void renderScreen()
{
    int x = 0;
    int y = 0;

    if (!glutGetWindow())
        return ;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glScalef(1.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

//    float x = glData.objWidth;
//    float y = glData.objHeight;
//    glBegin(GL_LINES);
//    for (float f = -1.0f; f <= 1.0; f += 2.0/(x))
//    {
//        glVertex2f(f, -1);
//        glVertex2f(f, 1);
//    }
//    for (float f = -1.0f; f <= 1.0; f += 2.0/(y))
//    {
//        glVertex2f(-1, f);
//        glVertex2f(1, f);
//    }
//    glEnd();
    glColor3f(255.0f, 0.0f, 0.0f);
    glTranslatef(-1.0f, -1.0f, 0.0f);
    glBegin(GL_QUADS);
    float playerx = glData.playerPosX;
    playerx = playerx / (glData.winWidth / 2);
    float playery = glData.playerPosY;
    playery = playery / (glData.winHeight / 2);
//    float objw = glData.objWidth;
//    objw = objw / 100;
//    objw = objw * 2;
//    float objh = glData.objHeight;
//    objh = objh / 100;
//    objh = objh * 2;
    float width;
    width = 2;
    width = width / glData.winWidth;
    float height;
    height = 2;
    height = height / glData.winHeight;
//    glVertex2f((playerx * objw) + width, (playery * (objh)) + height);
//    glVertex2f((playerx * objw) + width, (playery) * objh);
//    glVertex2f((playerx) * objw, (playery) * objh);
//    glVertex2f((playerx) * objw, (playery * objh) + height);3
    glVertex2f(playerx + width, playery + height);
    glVertex2f(playerx + width, playery);
    glVertex2f(playerx, playery);
    glVertex2f(playerx, playery + height);
    glEnd();

    glColor3f(0.0f, 255.0f, 0.0f);
    for (int i = 1; i <= glData.playerBody.size(); i++)
    {
        float playerBodyX = glData.playerBody[x][y];
        playerBodyX = playerBodyX / (glData.winWidth / 2);
        ++y;
        float playerBodyY = glData.playerBody[x][y];
        playerBodyY = playerBodyY / (glData.winHeight / 2);
        --y;
        ++x;
        glBegin(GL_QUADS);
        glVertex2f(playerBodyX + width, playerBodyY + height);
        glVertex2f(playerBodyX + width, playerBodyY);
        glVertex2f(playerBodyX, playerBodyY);
        glVertex2f(playerBodyX, playerBodyY + height);
        glEnd();
    }
    glColor3f(0.0f, 0.0f, 255.0f);
    glBegin(GL_QUADS);
    float foodX = glData.foodPosX;
    foodX = foodX / (glData.winWidth / 2);
    float foodY = glData.foodPosY;
    foodY = foodY / (glData.winHeight / 2);
    glVertex2f(foodX + width, foodY + height);
    glVertex2f(foodX + width, foodY);
    glVertex2f(foodX, foodY);
    glVertex2f(foodX, foodY + height);
    glEnd();
//    glBegin(GL_QUADS);
//    glVertex3f(0.1f, 0.1f, -5.0f);
//    glVertex3f(0.1f, -0.1f, -5.0f);
//    glVertex3f(-0.1f, -0.1f, -5.0f);
//    glVertex3f(-0.1f, 0.1f, -5.0f);
//    glEnd();
//    std::cout << "calc: " << (glData.playerPosX * glData.objWidth) << " " << (glData.playerPosY * glData.objHeight) << std::endl;

//    glBegin(GL_TRIANGLES); //Begin triangle coordinates
//
//    //Pentagon
//    glVertex3f(0.5f, 0.5f, -5.0f);
//    glVertex3f(1.5f, 0.5f, -5.0f);
//    glVertex3f(0.5f, 1.0f, -5.0f);
//
//    glVertex3f(0.5f, 1.0f, -5.0f);
//    glVertex3f(1.5f, 0.5f, -5.0f);
//    glVertex3f(1.5f, 1.0f, -5.0f);
//
//    glVertex3f(0.5f, 1.0f, -5.0f);
//    glVertex3f(1.5f, 1.0f, -5.0f);
//    glVertex3f(1.0f, 1.5f, -5.0f);
//
//    glVertex3f(-0.5f, 0.5f, -5.0f);
//    glVertex3f(-1.0f, 1.5f, -5.0f);
//    glVertex3f(-1.5f, 0.5f, -5.0f);
//
//    glEnd();

    glutSwapBuffers();
}

renderData render(renderData rdata)
{
    glData = rdata;
    glutPostRedisplay();
    glutMainLoopEvent();
    return glData;
}

void clean()
{
    glutLeaveMainLoop();
    return ;
}