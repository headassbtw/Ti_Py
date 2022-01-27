#pragma once

#include <Python.h>

struct py_vars{
    static PyObject* recall_ls(PyObject *self, PyObject *args);  
    static PyObject* store_ls(PyObject *self, PyObject *args);
};