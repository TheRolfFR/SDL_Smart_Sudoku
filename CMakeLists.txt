cmake_minimum_required(VERSION 3.0)

set (PROJECT_NAME untitled)
project(${PROJECT_NAME})

# C++ flags
set(SDL2_Flags "-mwindows -Wl,--no-undefined -static-libgcc -lSDL_ttf")


#dependencies paths
set(DEP_ROOT     "${PROJECT_SOURCE_DIR}/dependencies")
set(DEP_INCLUDES "${DEP_ROOT}/include")
set(DEP_LIBRARIES   "${DEP_ROOT}/lib")

# imported targets for CMake (cf. https://cmake.org/Wiki/CMake/Tutorials/Exporting_and_Importing_Targets)
add_library(SDL2      STATIC IMPORTED)
add_library(SDL2dll   STATIC IMPORTED)
add_library(SDL2main  STATIC IMPORTED)
add_library(SDL_image STATIC IMPORTED)

add_library(freetype STATIC IMPORTED)

add_library(SDL_TTF STATIC IMPORTED)

#include libs

set_property(TARGET SDL2     PROPERTY IMPORTED_LOCATION "${DEP_LIBRARIES}/libSDL2.a")
set_property(TARGET SDL2main PROPERTY IMPORTED_LOCATION "${DEP_LIBRARIES}/libSDL2main.a")
set_property(TARGET SDL2dll  PROPERTY IMPORTED_LOCATION "${DEP_LIBRARIES}/libSDL2.dll.a")
SET_PROPERTY(TARGET SDL_image PROPERTY IMPORTED_LOCATION "${DEP_LIBRARIES}/libSDL2_image.a")

set_property(TARGET freetype PROPERTY IMPORTED_LOCATION "${DEP_ROOT}/bin/libfreetype-6.dll")

set(SDL_TTF_INCLUDE_DIR "${DEP_ROOT}/include")
set(SDL_TTF_LIBRARIES "${DEP_ROOT}/lib")
find_package(SDL_ttf)
set_property(TARGET SDL_TTF  PROPERTY IMPORTED_LOCATION "${DEP_LIBRARIES}/libSDL2_ttf.a")


# note: as always with gcc, the order is important...
set(Libs mingw32 SDL2main SDL2 SDL_image freetype SDL_TTF m dinput8 dxguid dxerr8 user32 gdi32 winmm imm32 ole32 oleaut32 shell32 version uuid)

# configure the project
# include the SDL flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ${SDL2_Flags}")

# collect the sources
FILE(GLOB MyCSources *.c)
FILE(GLOB MySudokuSources sudoku_lib/*.c)
message(${MySudokuSources})
set(SOURCES ${MyCSources} ${MySudokuSources})
set(SOURCE_FILES ${SOURCES})

# define the target
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# include the SDL headers
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${DEP_INCLUDES})

# link against the SDL (and its dependencies)
target_link_libraries(${PROJECT_NAME} ${Libs})
