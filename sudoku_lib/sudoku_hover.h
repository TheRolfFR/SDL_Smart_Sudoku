//
// Created by TheRolf on 03/05/2019.
//

#ifndef SDL_SUDOKU_SUDOKU_HOVER_H
#define SDL_SUDOKU_SUDOKU_HOVER_H

#include "sdl_sudoku.h"

void drawNumberButtonsBackground(sudokuGrid*, SDL_Color *);
void drawAvailableNumbers(sudokuGrid*);


void drawNumberAtPosition(sudokuGrid*, cell*);

void drawNumberBackground(sudokuGrid*, cell*);

int hasPencilMark(cell*);

void updateHover(sudokuGrid*, cell*);

void printRect(sudokuGrid*, cell*, SDL_Color*);
void printHover(sudokuGrid*, cell*);
void removeHover(sudokuGrid*, cell*);

cell* getMousePosition(sudokuGrid*);

#endif //SDL_SUDOKU_SUDOKU_HOVER_H
