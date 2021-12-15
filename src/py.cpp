#include <iostream>
#include <fstream>
#include <Python.h>
#include <py.hpp>

void Import(const char* filename){
    std::ifstream inFile;
    inFile.open(filename);
    std::string str;
    std::string file_contents;
    while (std::getline(inFile, str))
    {
        file_contents += str;
        file_contents.push_back('\n');
    }
    PyRun_SimpleString(file_contents.c_str());
}