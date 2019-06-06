//
// Created by TheRolf on 21/05/2019.
//

#ifndef SDL_SUDOKU_PRINT_H
#define SDL_SUDOKU_PRINT_H

#include "sdl_sudoku.h"
void printRed(cell*);
void drawNumberButtonsBackground(SDL_Color *);
void drawAvailableNumbers();

void printRect(cell*, SDL_Color*);
void printHover(cell*);
void removeHover(cell*);
void drawNumberAtPosition(cell*);

void drawNumberBackground(cell*);
#endif //SDL_SUDOKU_PRINT_H
