#include "SDL_pixels.h"
#include "SDL_render.h"
#include <Python.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <py.hpp>
#include <pysdl.hpp>
#include <main.hpp>


float map_window(float value, bool axis){
    
    
    int h = Globals::screen_height * Globals::screen_size_mod;
    int w = Globals::screen_width * Globals::screen_size_mod;

    if(axis){
        return ((value - Globals::xmin) / (Globals::xmax - Globals::xmin)) * w;
    }
    else{
        return h - (((value - Globals::ymin) / (Globals::ymax - Globals::ymin)) * h);
    }
    std::cout << "invalid" << std::endl;
    return 0;
}


static PyObject*
color(PyObject *self, PyObject *args)
{
    float r;
    float g;
    float b;

    auto a = PyArg_ParseTuple(args,"fff", &r,&g,&b);
    if(a == 1){
        SDL_SetRenderDrawColor(Globals::renderer, r, g, b, SDL_ALPHA_OPAQUE);
    }
    return PyLong_FromLong(1);
}




static PyObject*
grid(PyObject *self, PyObject *args)
{
    Uint8 xsc;
    Uint8 ysc;
    const char* style;

    auto a = PyArg_ParseTuple(args,"IIs", &xsc,&ysc,&style);
    if(a == 1){
        SDL_SetRenderDrawColor(Globals::renderer, 120, 120, 120, SDL_ALPHA_OPAQUE);
        for(int i = Globals::xmin; i < (Globals::xmax-Globals::xmin);i+=xsc){
            SDL_RenderDrawLine(Globals::renderer, map_window(i, true), map_window(Globals::ymax, false), map_window(i, true), map_window(Globals::ymin, false));
        }
        for(int i = Globals::ymin; i < (Globals::ymax-Globals::ymin);i+=ysc){
            SDL_RenderDrawLine(Globals::renderer, map_window(Globals::xmin, true), map_window(i, false), map_window(Globals::xmax, true), map_window(i, false));
        }
    }
        
    return PyLong_FromLong(2);
}

static PyObject*
window(PyObject *self, PyObject *args)
{
    int xmin;
    int ymin;
    int xmax;
    int ymax;
    const char* style;

    auto a = PyArg_ParseTuple(args,"IIII", &xmin,&ymin,&xmax,&ymax);
    if(a == 1){
        Globals::xmin = xmin;
        Globals::xmax = xmax;
        Globals::ymin = ymin;
        Globals::ymax = ymax;
    }
        
    return PyLong_FromLong(2);
}



static PyObject*
cls(PyObject *self, PyObject *args)
{
    auto a = PyArg_ParseTuple(args,":cls");
    if(a == 1){
        SDL_SetRenderDrawColor(Globals::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(Globals::renderer);
        SDL_RenderPresent(Globals::renderer);
    }
        
    return PyLong_FromLong(2);
}



static PyObject*
line(PyObject *self, PyObject *args)
{
    float x1;
    float y1;
    float x2;
    float y2;

    auto a = PyArg_ParseTuple(args,"ffff", &x1,&y1,&x2,&y2);
    if(a == 1){
        int r = Globals::screen_size_mod;
        for(int i = 0; i < r; i++){
            for(int j = 0; j < r; j++){
                SDL_RenderDrawLine(Globals::renderer, map_window(x1, true)+i, map_window(y1, false)+j, map_window(x2, true)+i, map_window(y2, false)+j);
            }
        }        
    }
        
    return PyLong_FromLong(2);
}

static PyObject*
plot(PyObject *self, PyObject *args)
{
    float x;
    float y;
    const char* style;
    auto a = PyArg_ParseTuple(args,"ffs", &x,&y,&style);
    if(a == 1){
        int r = Globals::screen_size_mod;
        for(int i = 0; i < r; i++){
            for(int j = 0; j < r; j++){
                SDL_RenderDrawPoint(Globals::renderer, map_window(x, true)+i, map_window(y, false)+j);
            }
        }


        
    }
        
    return PyLong_FromLong(2);
}






static PyMethodDef SdlMethods[] = {
     {"color", color, METH_VARARGS,
     "Set pen color"},
     {"line", line, METH_VARARGS,
     "Draw a line"},
     {"plot", plot, METH_VARARGS,
     "Draw a point"},
     {"cls", cls, METH_VARARGS,
     "Clears the screen"},
     {"grid", grid, METH_VARARGS,
     "Draws a grid"},
     {"window", window, METH_VARARGS,
     "Sets the window size [BETA]"},
    {NULL, NULL, 1, NULL}
};

static PyModuleDef SdlModule = {
    PyModuleDef_HEAD_INIT, "ti_plotlib", NULL, -1, SdlMethods,
    NULL, NULL, NULL, NULL
};

PyObject*
py_sdl::PyInit_sdl(void)
{
    return PyModule_Create(&SdlModule);
}
