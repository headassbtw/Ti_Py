#include "SDL_render.h"
#include<frontend/statusbar.hpp>
#include <main.hpp>
#include <SDL2/SDL.h>



void StatusBar::RenderLoop(){
    SDL_SetRenderDrawColor(Globals::renderer, 255, 0, 0, 255);
    
    int h = Globals::statusbar_height;
    int y = h + Globals::screen_height;
    int w = Globals::screen_width;

    

    for(int i = 0; i < (w+h)/20; i++){
        int p = i * 20;

        


        for(int j = 0; j < 20; j++){
            if(j == 10)
                SDL_SetRenderDrawColor(Globals::renderer, 0, 0, 0, 155);
            if (j == 19)
                SDL_SetRenderDrawColor(Globals::renderer, 100, 100, 100, 155);

            SDL_RenderDrawLine(Globals::renderer,p+j,Globals::screen_height,(p-h)+j,y);
        }

        
    }
    for(int i = 0; i < h; i++){
        //SDL_SetRenderDrawColor(Globals::renderer, 0, 0, ((i/h)*255),0);
        //SDL_RenderDrawLine(Globals::renderer,0,Globals::screen_height+i,Globals::screen_width,Globals::screen_height+i);
    }


    /*for(int i = 0; i < h; i++){
        SDL_RenderDrawLine(Globals::renderer, 0, Globals::screen_height + i, Globals::screen_width, Globals::screen_height + i);
    }*/
}