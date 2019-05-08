//
// Created by TheRolf on 03/05/2019.
//

#ifndef SDL_SUDOKU_SUDOKU_CELL_H
#define SDL_SUDOKU_SUDOKU_CELL_H

#include "sudoku_grid.h"

typedef struct cell_struct {
    int number;
    int line;
    int column;
    char isHovered;
    char isClicked;
    char isReadOnly;
} cell;

cell *initCell(int, int, int, char, char);
void printCell(cell*);

#endif //SDL_SUDOKU_SUDOKU_CELL_H
