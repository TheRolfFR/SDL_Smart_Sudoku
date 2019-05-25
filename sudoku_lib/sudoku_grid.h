//
// Created by TheRolf on 03/05/2019.
//

#ifndef SDL_SUDOKU_GRID_H
#define SDL_SUDOKU_GRID_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "sudoku_cell.h"

/* Constantes de la grille */
#define GRID_THICK_BORDER 2
#define GRID_THIN_BORDER 1
#define GRID_CELL_SIZE 60
#define GRID_MARGIN 10
#define BUTTON_HEIGHT GRID_CELL_SIZE/2
#define GRID_BOTTOMSPACE GRID_CELL_SIZE + GRID_MARGIN + BUTTON_HEIGHT
#define GRID_SIZE GRID_CELL_SIZE*9 + GRID_THIN_BORDER*6 + GRID_THICK_BORDER * 2
#define BUTTON_WIDTH GRID_SIZE / 3
#define BUTTON_Y_OFFSET GRID_MARGIN*3 + GRID_SIZE + GRID_CELL_SIZE
#define GRID_FONT_SIZE GRID_CELL_SIZE
#define GRID_HOVER_BORDER 2
#define EMPTY_VALUE -1

#define TAILLE_MAX 200

typedef struct sudoku_grid {
    char initialTitle[TAILLE_MAX];
    SDL_Window *window;
    SDL_Surface *windowSurface;
    SDL_Renderer *renderer;
    TTF_Font *font;
    cell* lastHovered;
    cell* lastClicked;
    cell* cells[9][9];
    char pencilMarkMode;
    char emptyCell;
    char redHover;
    char lastKeyWasCtrl;
    int typedNumber;
    struct s_button* easy;
    struct s_button* normal;
    struct s_button* hard;
} sudokuGrid;

void tryInitGridFont();

int loadGrid(char*, int);

void drawSudokuGrid();

#endif //SDL_SUDOKUGRID_H
