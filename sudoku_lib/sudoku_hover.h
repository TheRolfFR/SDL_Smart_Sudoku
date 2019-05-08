//
// Created by TheRolf on 03/05/2019.
//

#ifndef SDL_SUDOKU_SUDOKU_HOVER_H
#define SDL_SUDOKU_SUDOKU_HOVER_H

#include "sdl_sudoku.h"

void drawNumbersBackground(sudokuGrid*);

void updateNumberAtPosition(sudokuGrid*, cell*, char, char);
void drawNumberAtPosition(sudokuGrid*, cell*, SDL_Color*);

void drawHoverBackground(sudokuGrid*);
void calculatePositionAndUpdate(sudokuGrid*, cell* [][9]);

void updateHover(cell*, sudokuGrid*);
void printHover(cell*);
void removeHover(cell*);
cell* getMousePosition(sudokuGrid*);

#endif //SDL_SUDOKU_SUDOKU_HOVER_H
