#pragma once
#include <SDL2/SDL.h>
struct Globals{
    static const char* fontpath;
    static SDL_Color color;
    static SDL_Renderer* renderer;
    static SDL_Renderer* post_renderer;
    static SDL_Window* window;
    static int statusbar_height;
    static int screen_size_mod;
    static int screen_width;
    static int screen_height;
    static float xmin;
    static float xmax;
    static float ymin;
    static float ymax;
    static bool done;
};