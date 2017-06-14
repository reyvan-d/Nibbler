//
// Created by Reyno VAN DER WESTHUIZEN on 2017/06/09.
//
#include <SDL.h>
#include "lib1.h"
#include "cleanup.h"

SDL_Window *win;
SDL_Renderer *ren;
SDL_Surface *bmp;
SDL_Texture *tex;

void initialize(renderData rdata) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return;
    }
    win = SDL_CreateWindow("Nibbler", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, rdata.winWidth, rdata.winHeight,
                           SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
        //SDL_DestroyWindow(win);
        cleanup(win);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }
    bmp = SDL_LoadBMP("../Crab Nebula.bmp");
    if (bmp == nullptr) {
        //SDL_DestroyRenderer(ren);
        //SDL_DestroyWindow(win);
        cleanup(ren, win);
        std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }
    tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);
    if (tex == nullptr)
    {
        //SDL_DestroyRenderer(ren);
        //SDL_DestroyWindow(win);
        cleanup(bmp, ren, win);
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return ;
    }
    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, tex, NULL, NULL);
    SDL_RenderPresent(ren);

}

void render(Engine *engine)
{

}