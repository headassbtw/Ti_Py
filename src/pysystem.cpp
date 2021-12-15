#include "SDL_events.h"
#include "SDL_render.h"
#include <pysystem.hpp>
#include <main.hpp>
#include <SDL2/SDL.h>



static PyObject*
dispwait(PyObject *self, PyObject *args)
{
    auto a = PyArg_ParseTuple(args,":disp_wait");
    if(a == 1){
        bool finished = false;
        SDL_RenderPresent(Globals::renderer);
        while(!finished){
            SDL_Event event;
            while (SDL_PollEvent(&event)){      
                switch(event.type){
                    case SDL_KEYDOWN:
                        finished = SDL_TRUE;
                    break;
                }
            }
            SDL_Delay(20);
        }
        
    }
        
    return PyLong_FromLong(2);
}






static PyMethodDef SysMethods[] = {
     {"disp_wait", dispwait, METH_VARARGS,
     "waits for key input"},
    {NULL, NULL, 1, NULL}
};

static PyModuleDef SysModule = {
    PyModuleDef_HEAD_INIT, "ti_plotlib", NULL, -1, SysMethods,
    NULL, NULL, NULL, NULL
};

PyObject*
py_system::PyInit_system(void)
{
    return PyModule_Create(&SysModule);
}
