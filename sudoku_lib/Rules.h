//
// Created by TheRolf on 10/05/2019.
//

#ifndef SDL_SUDOKU_RULES_H
#define SDL_SUDOKU_RULES_H

#include "sdl_sudoku.h"

void initRules();

cellList* addRule(cellList*, cell*);
cellList* removeRule(cellList*, cell*);

void addRules();
void removeRules();


void showRules(cellList* currentElement);
void hideRules(cellList* currentElement);

#endif //SDL_SUDOKU_RULES_H
