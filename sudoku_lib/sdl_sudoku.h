//
// Created by TheRolf on 03/05/2019.
//

#ifndef CONST_SDL_SUDOKU

#define CONST_SDL_SUDOKU

#endif

#include <string.h>
#include "../sdl_custom_lib.h"
#include "sudokuGrid.h"
#include "sudokuCell.h"
#include "sudokuHover.h"
#include "initializeSudoku.h"
#include "gameController.h"
#include "cellSelection.h"
#include "keyInterpretor.h"
#include "updateCellValue.h"
#include "moveSelected.h"
#include "changeTitleMode.h"
#include "Rules.h"
#include "victoryWindow.h"
#include "Print.h"
#include "undo.h"
#include "difficultyButton.h"
#include "freeMemory.h"

#ifndef SDL_SUDOKU_H
#define SDL_SUDOKU_H

char *convertInt(int);

#endif //SDL_SUDOKU_H
