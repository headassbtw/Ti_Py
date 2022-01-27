
#set(CMAKE_STSTEM_NAME Windows)
#set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-c++)



cmake_minimum_required(VERSION 3.22)
project(TiPy)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake_Modules/")
#INCLUDE("${CMAKE_CURRENT_SOURCE_DIR}/CMake_Modules/FindSDL2TTF.cmake")

find_package(Python3 COMPONENTS Interpreter Development)
find_package(SDL2 REQUIRED)
find_package(SDL2TTF REQUIRED)
include_directories(include)
include_directories(extern/RSJp-cpp)
include_directories(${Python3_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2TTF_INCLUDE_DIRS})

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
     "src/*.cpp"
     "include/*.hpp"
)


add_executable(TiPy ${SRC})

target_link_libraries(TiPy SDL2_ttf ${SDL2_LIBRARIES} ${Python3_LIBRARIES})
