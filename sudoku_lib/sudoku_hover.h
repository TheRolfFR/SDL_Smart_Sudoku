//
// Created by TheRolf on 03/05/2019.
//

#ifndef SDL_SUDOKU_SUDOKU_HOVER_H
#define SDL_SUDOKU_SUDOKU_HOVER_H

#include "sdl_sudoku.h"

void drawNumberButtonsBackground(SDL_Color *);
void drawAvailableNumbers();


void drawNumberAtPosition(cell*);

void drawNumberBackground(cell*);

int hasPencilMark(cell*);

void updateHover(cell*);

void printRect(cell*, SDL_Color*);
void printHover(cell*);
void removeHover(cell*);

cell* getMousePosition();

#endif //SDL_SUDOKU_SUDOKU_HOVER_H
