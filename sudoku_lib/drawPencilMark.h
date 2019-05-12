//
// Created by TheRolf on 10/05/2019.
//

#ifndef SDL_SUDOKU_DRAWPENCILMARK_H
#define SDL_SUDOKU_DRAWPENCILMARK_H

#include "sdl_sudoku.h"

void removePencilMark(sudokuGrid*, cell*, int);
void drawPencilMark(sudokuGrid*, cell*, int);

void ChangeTitleMode(sudokuGrid*);

#endif //SDL_SUDOKU_DRAWPENCILMARK_H
