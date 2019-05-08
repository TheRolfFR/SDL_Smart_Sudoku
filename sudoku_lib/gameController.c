//
// Created by asus on 08/05/2019.
//

#include "sdl_sudoku.h"

void gameController(sudokuGrid* data){
    char play=1;
    cell* position = getMousePosition(data);

    while (play){
        updateHover(position,data);
        
    }
}
