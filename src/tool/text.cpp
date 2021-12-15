#include <cctype>
#include <cstring>
#include <string>
#include <tool/text.hpp>
#include <SDL2/SDL_rect.h>
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <main.hpp>

void Text::Draw(int x, int y, const char* text, const char* align){
    std::cout << "Creating text element" << std::endl;
    TTF_Font* Font;
    Font = TTF_OpenFont(Globals::fontpath, 18);
    if(Font == NULL){
        std::cout << "Could not load font" << std::endl;
    }
    else{
        std::cout << "Font loaded" << std::endl;
    }
    int fw;int fh;
    TTF_SizeText(Font, "A", &fw, &fh);
    std::cout << "font is" + std::to_string(fw) + "x" + std::to_string(fh) << std::endl;



    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Font, text, Globals::color); 
    SDL_Texture* Message = SDL_CreateTextureFromSurface(Globals::renderer, surfaceMessage);
    int w; int h;
    TTF_SizeText(Font, text, &w, &h);
    SDL_Rect* a = new SDL_Rect();
    a->h = h;
    a->w = w;
    a->x = x;
    a->y = y;
    

    int txth = w/2;

    if(strcmp(align, "left") == 0){
        a->x = x;
        std::cout << "left" << std::endl;
    }
    else if(strcmp(align, "center") == 0){
        a->x = ((Globals::screen_width /2) - txth);
        std::cout << "center" << std::endl;
    }
    else if(strcmp(align, "right") == 0){
        a->x = (Globals::screen_width - w);
        std::cout << "right" << std::endl;
    }
    SDL_RenderCopy(Globals::renderer, Message, NULL, a);
    
    if(Message != nullptr)
        SDL_DestroyTexture(Message);
    if(surfaceMessage != nullptr)
        SDL_FreeSurface(surfaceMessage);




}