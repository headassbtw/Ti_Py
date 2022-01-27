#include <cstdlib>
#include <fstream>
#include <pyvars.hpp>

#include "SDL_events.h"
#include "SDL_render.h"
#include "SDL_ttf.h"
#include "floatobject.h"
#include "listobject.h"
#include "longobject.h"
#include "object.h"
#include "unicodeobject.h"
#include <pysystem.hpp>
#include <main.hpp>
#include <SDL2/SDL.h>
#include <sdl.hpp>
#include <string>
#include <tool/text.hpp>
#include <frontend/statusbar.hpp>
#include <iostream>
#include <RSJparser.tcc>
#include <vector>

RSJresource json_file_resource;

void checkjson(){
    std::ifstream f("vars.json");
    if(f.good() && f.peek() != std::ifstream::traits_type::eof()){
      f.close();
    }
    else{
      std::ofstream of("vars.json");
      of << "{\n     \n}";
      of.close();
    }
}


void ls_write(const char* name, const char* contents){
  checkjson();
  std::ifstream my_fstream ("vars.json");
    RSJresource json_file_resource (my_fstream);
    my_fstream.close();
    std::ofstream out_str("vars.json");
    json_file_resource[name] = contents;
    out_str.clear();
    out_str << json_file_resource.as_str();
}

RSJarray ls_read(const char* name){
  checkjson();
  std::ifstream my_fstream ("vars.json");
    RSJresource json_file_resource (my_fstream);
    my_fstream.close();
    return json_file_resource[name].as_array();
}


PyObject*
py_vars::recall_ls(PyObject *self, PyObject *args)
{
    const char* name;
    auto a = PyArg_ParseTuple(args,"s",&name);
    if(a == 1){
        auto ls = ls_read(name);
        PyObject* rtn = PyList_New(ls.size());
        for(int i = 0; i < ls.size(); i++){
          auto f = ls[i].as_str();

          if(f.at(0) == '"'){//is a string
            auto t = f.substr(1, f.size()-2);
            PyList_SetItem(rtn, i, PyUnicode_FromString(t.c_str()));
          }
          else{ //number or sumn
            PyList_SetItem(rtn, i, PyFloat_FromString(PyUnicode_FromString(f.c_str())));
          }
        }
        return rtn;
    }
    return PyLong_FromLong(2);
}
PyObject*
py_vars::store_ls(PyObject *self, PyObject *args)
{
    const char* name;
    PyObject* list;
    auto a = PyArg_ParseTuple(args,"sO",&name,&list);
    if(a == 1){
      int listsize = PyList_GET_SIZE(list);
      if(listsize >= 1){ 
        std::string write;
        write += "[";
          for(int i = 0; i < listsize; i++){
            auto item = PyList_GetItem(list, i);
            if(strcmp(item->ob_type->tp_name, "str") == 0){
              auto f = PyUnicode_AsUTF8(PyObject_Str(item));
              write += "\"";
              write += f;
              write += "\"";
            }
            else{
              float xx = PyLong_AsDouble(item);
              write += std::to_string(xx);
            }
            if(i < listsize-1) write += ",";
          }
          write += "]";
          ls_write(name,write.c_str());
      } //if listsize
    }
    
    return PyLong_FromLong(2);
}
