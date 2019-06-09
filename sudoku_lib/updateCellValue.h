//
// Created by TheRolf on 09/05/2019.
//

#ifndef SDL_SUDOKU_UPDATECELLVALUE_H
#define SDL_SUDOKU_UPDATECELLVALUE_H

#include "sdl_sudoku.h"

void updateCellValue();
int  hasPencilMark(cell*);
void resetPencilMark(cell*);
void clearCell();

#endif //SDL_SUDOKU_UPDATECELLVALUE_H
