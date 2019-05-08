//
// Created by TheRolf on 03/05/2019.
//

#ifndef SDL_SUDOKU_SUDOKU_HOVER_H
#define SDL_SUDOKU_SUDOKU_HOVER_H

#include "sdl_sudoku.h"

void drawNumbersBackground(sudokuGrid*);

void drawNumberAtPosition(sudokuGrid*, cell*);

void drawHoverBackground(sudokuGrid*);
void calculatePositionAndUpdate();

void updateHover(sudokuGrid*, cell*);

void printRect(sudokuGrid*, cell*, SDL_Color*);
void printHover(sudokuGrid*, cell*);
void removeHover(sudokuGrid*, cell*);

cell* getMousePosition(sudokuGrid*);

#endif //SDL_SUDOKU_SUDOKU_HOVER_H
