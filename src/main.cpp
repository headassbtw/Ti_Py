#include <iostream>
#include <filesystem>
#include <fstream>
#include <Python.h>
#include <string>
#include "SDL.h"
#include <main.hpp>
#include <unistd.h>
#include "SDL_pixels.h"
#include "SDL_render.h"
#include "SDL_surface.h"
#include "SDL_timer.h"
#include "SDL_ttf.h"
#include "SDL_video.h"
#include <py.hpp>
#include <pysdl.hpp>
#include <pysystem.hpp>

#include <tool/text.hpp>

const char* Globals::fontpath;
SDL_Color Globals::color = {0,0,0};
SDL_Window* Globals::window;
SDL_Renderer* Globals::renderer;
int Globals::screen_size_mod = 1;
int Globals::screen_width = 320;
int Globals::screen_height = 210;
float Globals::xmin = -10;
float Globals::xmax = 10;
float Globals::ymin = -6.56;
float Globals::ymax = 6.56;
bool Globals::done = false;





int main(int argc, char* argv[]){
    
    



    if(argc <= 1){
        std::cout << "Invalid arguments" << std::endl;
        return 1;
    }
    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        std::cout << "Fatal error: cannot decode argv[0]" << std::endl;
        exit(1);
    }
    if(TTF_Init() == 0){
        std::cout << "TTF engine initialized" << std::endl;
    }
    else{
        std::cout << "could not start TTF engine" << std::endl;
    }
    //SDL_CreateWindowAndRenderer(320, 210, SDL_WINDOW_VULKAN, &window, &renderer);
    SDL_CreateWindowAndRenderer(Globals::screen_width * Globals::screen_size_mod, Globals::screen_height * Globals::screen_size_mod, SDL_WINDOW_VULKAN, &Globals::window, &Globals::renderer);
    std::string pyname = argv[1];
    std::cout << "Running file ";
    std::cout << pyname << std::endl;
    
    std::string wintitle = "TiPy - " + pyname;
    SDL_SetWindowTitle(Globals::window, wintitle.c_str());
    SDL_SetRenderDrawColor(Globals::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(Globals::renderer);
    SDL_RenderPresent(Globals::renderer);
    Py_SetProgramName(program);
    PyImport_AppendInittab("ti_plotlib", &py_sdl::PyInit_sdl);
    PyImport_AppendInittab("ti_system", &py_system::PyInit_system);
    Py_Initialize();

    //lets you import files from the same directory
    std::string pathcmd;
    char tmp[256];
    getcwd(tmp, 256);
    pathcmd += "sys.path.append('";
    pathcmd += tmp;
    pathcmd += "/')\n";
    PyRun_SimpleString("import sys\n");
    PyRun_SimpleString(pathcmd.c_str());
    std::string fontp = tmp;
    fontp+= "/font.ttf";
    Globals::fontpath = fontp.c_str();

    SDL_SetRenderDrawColor(Globals::renderer, Globals::color.r, Globals::color.g, Globals::color.b, SDL_ALPHA_OPAQUE);
    Import(pyname.c_str());

    /*
    std::ifstream inFile;
    inFile.open(pyname);
    std::string str;
    std::string file_contents;
    while (std::getline(inFile, str))
    {
        file_contents += str;
        file_contents.push_back('\n');
    }  

    PyRun_SimpleString(file_contents.c_str());*/
    SDL_RenderPresent(Globals::renderer);
    
    if (Py_FinalizeEx() < 0) {
        exit(120);
    }
    PyMem_RawFree(program);

    SDL_DestroyRenderer(Globals::renderer);
    SDL_DestroyWindow(Globals::window);
    SDL_Quit();
	return 0;

}
