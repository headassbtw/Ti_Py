#pragma once
#include <SDL2/SDL.h>
struct Globals{
    static SDL_Renderer* renderer;
    static SDL_Window* window;
    static int screen_size_mod;
    static int screen_width;
    static int screen_height;
    static float xmin;
    static float xmax;
    static float ymin;
    static float ymax;
    static bool done;
};