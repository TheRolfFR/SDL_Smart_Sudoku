//
// Created by TheRolf on 03/05/2019.
//

#ifndef SDL_SUDOKU_SUDOKUCELL_H
#define SDL_SUDOKU_SUDOKUCELL_H

#include "sudokuGrid.h"

typedef struct cellList{
    struct cell_struct* bloqueur;
    struct cellList* next;
}cellList;

typedef struct cell_struct {
    int number;
    int line;
    int column;
    char isHovered;
    char isClicked;
    char isReadOnly;
    cellList* rules[9];
    char pencilMark[9];
} cell;

cell *initCell(int, int, int, char, char);

#endif //SDL_SUDOKU_SUDOKUCELL_H
