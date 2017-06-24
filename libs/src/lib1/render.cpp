//
// Created by Reyno VAN DER WESTHUIZEN on 2017/06/09.
//
#include "lib1.h"
#include "cleanup.h"

SDL_Event event;
SDL_Window *win;
SDL_Renderer *ren;
SDL_Surface *bmp;
SDL_Texture *tex;

void initialize(renderData rdata)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return;
    }
    win = SDL_CreateWindow("Nibbler", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 480, 480, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
        cleanup(win);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }
    bmp = SDL_LoadBMP("textures/lib1/Crab Nebula.bmp");
    if (bmp == nullptr) {
        cleanup(ren, win);
        std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }
    tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);
    if (tex == nullptr) {
        cleanup(bmp, ren, win);
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }
}

void clean()
{
    cleanup(ren, win, tex);
    SDL_Quit();
    return ;
}

renderData render(renderData rdata)
{
    int x = 0;
    int y = 0;

    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, tex, NULL, NULL);
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
    SDL_Rect r;
    r.x = rdata.playerPosX * rdata.objWidth;
    // r.x = (480 / 2) - (rdata.objWidth / 2);
    r.y = rdata.playerPosY * rdata.objHeight;
    r.w = rdata.objWidth;
    r.h = rdata.objHeight;
    SDL_RenderFillRect(ren, &r);
    SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
    for (int i = 1; i <= static_cast<int>(rdata.playerBody.size()); i++)
    {
        r.x = rdata.playerBody[x][y] * rdata.objWidth;
        ++y;
        r.y = rdata.playerBody[x][y] * rdata.objHeight;
        --y;
        ++x;
        r.w = rdata.objWidth;
        r.h = rdata.objHeight;
        SDL_RenderFillRect(ren, &r);
    }
    SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
    r.x = rdata.foodPosX * rdata.objWidth;
    // r.x = (480 / 2) - (rdata.objWidth / 2);
    r.y = rdata.foodPosY * rdata.objHeight;
    r.w = rdata.objWidth;
    r.h = rdata.objHeight;
    SDL_RenderFillRect(ren, &r);
    SDL_RenderPresent(ren);
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_LEFT:
                        if (rdata.playerXDirection != 1 && !rdata.dir)
                        {
                            rdata.playerXDirection = -1;
                            rdata.playerYDirection = 0;
                            rdata.dir = true;
                        }
                        break;
                    case SDLK_RIGHT:
                        if (rdata.playerXDirection != -1 && !rdata.dir)
                        {
                            rdata.playerXDirection = 1;
                            rdata.playerYDirection = 0;
                            rdata.dir = true;
                        }
                        break;
                    case SDLK_UP:
                        if (rdata.playerYDirection != 1 && !rdata.dir)
                        {
                            rdata.playerXDirection = 0;
                            rdata.playerYDirection = -1;
                            rdata.dir = true;
                        }
                        break;
                    case SDLK_DOWN:
                        if (rdata.playerYDirection != -1 && !rdata.dir)
                        {
                            rdata.playerXDirection = 0;
                            rdata.playerYDirection = 1;
                            rdata.dir = true;
                        }
                        break;
                    case SDLK_2:
                        rdata.key = 2;
                        break;
                    case SDLK_3:
                        rdata.key = 3;
                        break;
                    case SDLK_ESCAPE:
                        rdata.key = 0;
                        break;
                }
        }
    }
    return rdata;
}