//
// Created by Andromaleus on 2017-06-08.
//

#include "lib3.h"

renderData glData;
int win;
GLuint * textures;
GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat light_position[] = {1.0f, 1.0f, 1.0f, -1.0f};
GLfloat light_position2[] = {1.0f, 0.0f, 0.0f, 1.0f};

void initialize(renderData rdata)
{
    glutInit(&rdata.ac, rdata.av);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_MULTISAMPLE | GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 720) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 720) / 2);
    glutInitWindowSize(720, 720);
    win = glutCreateWindow("Nibbler");
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 20);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 20);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    textures = new GLuint[4];
    glGenTextures(4, textures);
    LoadTextureRAW(textures[0], "textures/lib3/iron_texture2.data", 1, 256, 256);
    LoadTextureRAW(textures[1], "textures/lib3/head2.data", 1, 256, 256);
    LoadTextureRAW(textures[2], "textures/lib3/fur.data", 1, 256, 256);
    LoadTextureRAW(textures[3], "textures/lib3/GL_background.data", 1, 512, 512);
    glutDisplayFunc(&renderScreen);
    glutKeyboardFunc(handleKeypress);
    glutSpecialFunc(specialInput);
    glutReshapeFunc(handleResize);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

    glewInit();
    if (!GLEW_VERSION_2_1)
    {
        std::cerr << "OpenGL 3.3 not available" << std::endl;
        exit(1);
    }
    glEnable(GL_DEPTH_TEST);
    return ;
}

void LoadTextureRAW(GLuint texture, const char *filename, int wrap, int width, int height)
{
    unsigned char	*data;
    FILE			*file;

    // open texture data
    file = fopen( filename, "rb" );
    if (file == NULL)
    {
        return ;
    }

    // allocate buffer
    data = static_cast<unsigned char *>(malloc(static_cast<unsigned int>(width * height * 3)));

    // read texture data
    fread(data, static_cast<unsigned int>(width * height * 3), 1, file);
    fclose(file);

    // select modulate to mix texture with color for shading
//    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    // when texture area is small, bilinear filter the closest mipmap
//    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
//                     GL_LINEAR_MIPMAP_NEAREST );
    // when texture area is large, bilinear filter the first mipmap
//    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
//    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
    //                    wrap ? GL_REPEAT : GL_CLAMP );
//    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
//                     wrap ? GL_REPEAT : GL_CLAMP );

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    // build our texture mipmaps
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    // free buffer
    delete (data);
}

void specialInput(int key, int x, int y)
{
    static_cast<void>(x);
    static_cast<void>(y);
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
    static_cast<void>(x);
    static_cast<void>(y);
    switch(key)
    {
        case '1':
            glData.key = 1;
            break;
        case '2':
            glData.key = 2;
            break;
        case 27:
            glData.key = 0;
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

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(0, 2, 2, 0, -1, 1);
    glDepthMask(GL_FALSE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[3]);
    glBegin(GL_QUADS);

    glTexCoord2d(1, 1); glVertex3f(2, 2, -0.5f);
    glTexCoord2d(1, 0); glVertex3f(2, 0, -0.5f);
    glTexCoord2d(0, 0); glVertex3f(0, 0, -0.5f);
    glTexCoord2d(0, 1); glVertex3f(0, 2, -0.5f);

    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDepthMask(GL_TRUE);
    glLoadIdentity();
    glScalef(0.8f, -0.8f, 0.8f);
    glTranslatef(-0.7f, -1.0f, 0.1f);
    glRotatef(15.0f, 0.0f, 0.0f, 1.0f);
    glRotatef(-17.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(23.0f, 0.0f, 1.0f, 0.0f);

    float width;
    width = 2;
    width = width / glData.winWidth;
    float height;
    height = 2;
    height = height / glData.winHeight;

    float x1 = glData.objWidth;
    float y1 = glData.objHeight;
    glColor3f(0.40f, 1.0f, 0.10f);
    glBegin(GL_LINES);
    for (float f = 0.0f; f <= (2.0 + width); f += width)
    {
        glVertex3f(f, 0.0f, 0.1f);
        glVertex3f(f, 2.0f, 0.1f);
    }
    for (float f = 0.0f; f <= (2.0 + height); f += height)
    {
        glVertex3f(0.0f, f, 0.1f);
        glVertex3f(2.0f, f, 0.1f);
    }
    glEnd();

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

//    glVertex2f((playerx * objw) + width, (playery * (objh)) + height);
//    glVertex2f((playerx * objw) + width, (playery) * objh);
//    glVertex2f((playerx) * objw, (playery) * objh);
//    glVertex2f((playerx) * objw, (playery * objh) + height);3

    glColor3f(1.0f, 1.0f, 10.0f);
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[0]);

    for (int i = 1; i <= static_cast<int>(glData.playerBody.size()); i++)
    {
        float playerBodyX = glData.playerBody[x][y];
        playerBodyX = playerBodyX / (glData.winWidth / 2);
        ++y;
        float playerBodyY = glData.playerBody[x][y];
        playerBodyY = playerBodyY / (glData.winHeight / 2);
        --y;
        ++x;
        glBegin(GL_QUADS);

        glTexCoord2d(1, 1); glVertex3f(playerBodyX + width, playerBodyY + height, 0.0f);
        glTexCoord2d(1, 0); glVertex3f(playerBodyX + width, playerBodyY, 0.0f);
        glTexCoord2d(0, 0); glVertex3f(playerBodyX, playerBodyY, 0.0f);
        glTexCoord2d(0, 1); glVertex3f(playerBodyX, playerBodyY + height, 0.0f);

        glTexCoord2d(0, 0); glVertex3f(playerBodyX + width, playerBodyY + height, 0.0f);
        glTexCoord2d(0, 1); glVertex3f(playerBodyX + width, playerBodyY, 0.0f);
        glTexCoord2d(1, 1); glVertex3f(playerBodyX, playerBodyY, 0.0f);
        glTexCoord2d(1, 0); glVertex3f(playerBodyX, playerBodyY + height, 0.0f);

        glTexCoord2d(0, 0); glVertex3f(playerBodyX + width, playerBodyY + height, 0.1f);
        glTexCoord2d(0, 1); glVertex3f(playerBodyX + width, playerBodyY + height, 0.0f);
        glTexCoord2d(1, 1); glVertex3f(playerBodyX + width, playerBodyY, 0.0f);
        glTexCoord2d(1, 0); glVertex3f(playerBodyX + width, playerBodyY, 0.1f);

        glTexCoord2d(0, 0); glVertex3f(playerBodyX, playerBodyY + height, 0.1f);
        glTexCoord2d(0, 1); glVertex3f(playerBodyX, playerBodyY + height, 0.0f);
        glTexCoord2d(1, 1); glVertex3f(playerBodyX, playerBodyY, 0.0f);
        glTexCoord2d(1, 0); glVertex3f(playerBodyX, playerBodyY, 0.1f);

        glTexCoord2d(0, 0); glVertex3f(playerBodyX + width, playerBodyY, 0.1f);
        glTexCoord2d(0, 1); glVertex3f(playerBodyX + width, playerBodyY, 0.0f);
        glTexCoord2d(1, 1); glVertex3f(playerBodyX, playerBodyY, 0.0f);
        glTexCoord2d(1, 0); glVertex3f(playerBodyX, playerBodyY, 0.1f);

        glTexCoord2d(0, 0); glVertex3f(playerBodyX + width, playerBodyY + height, 0.1f);
        glTexCoord2d(0, 1); glVertex3f(playerBodyX + width, playerBodyY + height, 0.0f);
        glTexCoord2d(1, 1); glVertex3f(playerBodyX, playerBodyY + height, 0.0f);
        glTexCoord2d(1, 0); glVertex3f(playerBodyX, playerBodyY + height, 0.1f);

        glEnd();
    }
    glDisable(GL_TEXTURE_2D);

    float foodX = glData.foodPosX;
    foodX = foodX / (glData.winWidth / 2);
    float foodY = glData.foodPosY;
    foodY = foodY / (glData.winHeight / 2);

    glColor3f(178.0f, 0.0f, 255.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glBegin(GL_QUADS);

    glTexCoord2d(1, 1); glVertex3f(foodX + width, foodY + height, 0.0f);
    glTexCoord2d(1, 0); glVertex3f(foodX + width, foodY, 0.0f);
    glTexCoord2d(0, 0); glVertex3f(foodX, foodY, 0.0f);
    glTexCoord2d(0, 1); glVertex3f(foodX, foodY + height, 0.0f);

    glTexCoord2d(0, 0); glVertex3f(foodX + width, foodY + height, 0.0f);
    glTexCoord2d(0, 1); glVertex3f(foodX + width, foodY, 0.0f);
    glTexCoord2d(1, 1); glVertex3f(foodX, foodY, 0.0f);
    glTexCoord2d(1, 0); glVertex3f(foodX, foodY + height, 0.0f);

    glTexCoord2d(0, 0); glVertex3f(foodX + width, foodY + height, 0.1f);
    glTexCoord2d(0, 1); glVertex3f(foodX + width, foodY + height, 0.0f);
    glTexCoord2d(1, 1); glVertex3f(foodX + width, foodY, 0.0f);
    glTexCoord2d(1, 0); glVertex3f(foodX + width, foodY, 0.1f);

    glTexCoord2d(0, 0); glVertex3f(foodX, foodY + height, 0.1f);
    glTexCoord2d(0, 1); glVertex3f(foodX, foodY + height, 0.0f);
    glTexCoord2d(1, 1); glVertex3f(foodX, foodY, 0.0f);
    glTexCoord2d(1, 0); glVertex3f(foodX, foodY, 0.1f);

    glTexCoord2d(0, 0); glVertex3f(foodX + width, foodY, 0.1f);
    glTexCoord2d(0, 1); glVertex3f(foodX + width, foodY, 0.0f);
    glTexCoord2d(1, 1); glVertex3f(foodX, foodY, 0.0f);
    glTexCoord2d(1, 0); glVertex3f(foodX, foodY, 0.1f);

    glTexCoord2d(0, 0); glVertex3f(foodX + width, foodY + height, 0.1f);
    glTexCoord2d(0, 1); glVertex3f(foodX + width, foodY + height, 0.0f);
    glTexCoord2d(1, 1); glVertex3f(foodX, foodY + height, 0.0f);
    glTexCoord2d(1, 0); glVertex3f(foodX, foodY + height, 0.1f);

    glEnd();
    glDisable(GL_TEXTURE_2D);

    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_QUADS);

    glTexCoord2d(1, 1); glVertex3f(playerx + width, playery + height, 0.0f);
    glTexCoord2d(1, 0); glVertex3f(playerx + width, playery, 0.0f);
    glTexCoord2d(0, 0); glVertex3f(playerx, playery, 0.0f);
    glTexCoord2d(0, 1); glVertex3f(playerx, playery + height, 0.0f);

    glTexCoord2d(0, 0); glVertex3f(playerx + width, playery + height, 0.0f);
    glTexCoord2d(0, 1); glVertex3f(playerx + width, playery, 0.0f);
    glTexCoord2d(1, 1); glVertex3f(playerx, playery, 0.0f);
    glTexCoord2d(1, 0); glVertex3f(playerx, playery + height, 0.0f);

    glTexCoord2d(0, 0); glVertex3f(playerx + width, playery + height, 0.1f);
    glTexCoord2d(0, 1); glVertex3f(playerx + width, playery + height, 0.0f);
    glTexCoord2d(1, 1); glVertex3f(playerx + width, playery, 0.0f);
    glTexCoord2d(1, 0); glVertex3f(playerx + width, playery, 0.1f);

    glTexCoord2d(0, 0); glVertex3f(playerx, playery + height, 0.1f);
    glTexCoord2d(0, 1); glVertex3f(playerx, playery + height, 0.0f);
    glTexCoord2d(1, 1); glVertex3f(playerx, playery, 0.0f);
    glTexCoord2d(1, 0); glVertex3f(playerx, playery, 0.1f);

    glTexCoord2d(0, 0); glVertex3f(playerx + width, playery, 0.1f);
    glTexCoord2d(0, 1); glVertex3f(playerx + width, playery, 0.0f);
    glTexCoord2d(1, 1); glVertex3f(playerx, playery, 0.0f);
    glTexCoord2d(1, 0); glVertex3f(playerx, playery, 0.1f);

    glTexCoord2d(0, 0); glVertex3f(playerx + width, playery + height, 0.1f);
    glTexCoord2d(0, 1); glVertex3f(playerx + width, playery + height, 0.0f);
    glTexCoord2d(1, 1); glVertex3f(playerx, playery + height, 0.0f);
    glTexCoord2d(1, 0); glVertex3f(playerx, playery + height, 0.1f);

    glEnd();
    glDisable(GL_TEXTURE_2D);
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
    glutDestroyWindow(win);
    delete textures;
    glutExit();
    return ;
}