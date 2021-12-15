#include "SDL_events.h"
#include "SDL_render.h"
#include "SDL_ttf.h"
#include <pysystem.hpp>
#include <main.hpp>
#include <SDL2/SDL.h>
#include <string>
#include <tool/text.hpp>
#include <iostream>

static PyObject*
dispwait(PyObject *self, PyObject *args)
{
    auto a = PyArg_ParseTuple(args,":disp_wait");
    if(a == 1){
        bool finished = false;
        SDL_RenderPresent(Globals::renderer);
        while(!finished){
            SDL_RenderPresent(Globals::renderer); //this keeps the screen alive, very finnicky otherwise
            SDL_Event event;
            while (SDL_PollEvent(&event)){   
                                //771 is alphanumeric, from what i can tell
                if((/*event.type == SDL_KEYDOWN */ event.key.type == 771) || event.type == SDL_QUIT) finished = SDL_TRUE;
            }
            SDL_Delay(20);
        }
    }
    return PyLong_FromLong(2);
}

static PyObject*
disp_text(PyObject *self, PyObject *args)
{
    int row;
    const char* text;
    const char* align;

    auto a = PyArg_ParseTuple(args,"Iss",&row,&text,&align);
    if(a == 1){
        Text::Draw(0, 24*(row-1), text,align);
        SDL_RenderPresent(Globals::renderer);

        
    }
    return PyLong_FromLong(2);
}



static PyMethodDef SysMethods[] = {
     {"disp_wait", dispwait, METH_VARARGS,
     "waits for key input"},
     {"disp_at", disp_text, METH_VARARGS,
     "displays text"},
    {NULL, NULL, 1, NULL}
};

static PyModuleDef SysModule = {
    PyModuleDef_HEAD_INIT, "ti_system", NULL, -1, SysMethods,
    NULL, NULL, NULL, NULL
};

PyObject*
py_system::PyInit_system(void)
{
    return PyModule_Create(&SysModule);
}
