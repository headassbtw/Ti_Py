#include "SDL_render.h"
#include <cstring>
#include <sdl.hpp>
#include <SDL2/SDL.h>
#include <main.hpp>
#include <iostream>
void SDL::Clear(){
    SDL_SetRenderDrawColor(Globals::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(Globals::renderer);
    SDL_RenderPresent(Globals::renderer);
}
void SDL::Dot(int x, int y, const char* mark){
    int r = Globals::screen_size_mod;

    if(strcmp(mark, "o") == 0){ //circle
        for(int i = 0; i < 4; i++){         //do not question this
            for(int j = 0; j < 360; j++){   //i know it's absolutely horrible
                float tx = cos(j)*i;        //cry more
                float ty = sin(j)*i;
                SDL_RenderDrawPointF(Globals::renderer, tx+x, ty+y);
            }
        }
    }
    if(strcmp(mark, "+") == 0){ //plus
        for(int i = 0; i < 7; i++){
            SDL_RenderDrawPoint(Globals::renderer, x, (y-3)+i);
            SDL_RenderDrawPoint(Globals::renderer, (x-3)+i, y);
        }
    }
    if(strcmp(mark, "x") == 0){ //cross
        for(int i = 0; i < 7; i++){
            SDL_RenderDrawPoint(Globals::renderer, (x-3)+i, (y-3)+i);
            SDL_RenderDrawPoint(Globals::renderer, (x-3)+i, (y+3)-i);
        }
    }
    if(strcmp(mark, ".") == 0){ //pixel
        for(int i = 0; i < r; i++){
            for(int j = 0; j < r; j++){
                SDL_RenderDrawPoint(Globals::renderer, x+i, y+j);
            }
        }
    }
}