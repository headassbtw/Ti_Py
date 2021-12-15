//#pragma once
#include <Python.h>
float map_window(float value, bool axis);


struct py_sdl{
    static PyObject* PyInit_sdl(void);  
};