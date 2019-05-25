//
// Created by TheRolf on 25/05/2019.
//

#ifndef SDL_SUDOKU_DIFFICULTYBUTTON_H
#define SDL_SUDOKU_DIFFICULTYBUTTON_H

#include "sdl_sudoku.h"

typedef struct s_button {
    int x;
    int previouslyClicked;
} difficultyButton;

void fillAndDrawButton(difficultyButton*, char[]);
char isInButton(difficultyButton*, int, int);
void clickButton(difficultyButton*);
void unclickButton(difficultyButton*);
int handleDifficultyButtons();
int changeDifficulty(char[]);

#endif //SDL_SUDOKU_DIFFICULTYBUTTON_H
