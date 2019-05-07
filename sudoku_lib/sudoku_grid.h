//
// Created by TheRolf on 03/05/2019.
//

#ifndef SDL_SUDOKU_GRID_H
#define SDL_SUDOKU_GRID_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "sudoku_cell.h"

/* Constantes de masque NE PAS TOUCHER */
#define RED_MASK   0xFF000000
#define GREEN_MASK 0x00FF0000
#define BLUE_MASK  0x0000FF00
#define ALPHA_MASK 0x000000FF

/* Constantes de la grille */
#define GRID_THICK_BORDER 2
#define GRID_THIN_BORDER 1
#define GRID_CELL_SIZE 60
#define GRID_MARGIN 10
#define GRID_BOTTOMSPACE GRID_CELL_SIZE
#define GRID_SIZE GRID_CELL_SIZE*9 + GRID_THIN_BORDER*6 + GRID_THICK_BORDER * 2
#define GRID_FONT_SIZE GRID_CELL_SIZE
#define GRID_HOVER_BORDER 2

#define TAILLE_MAX 200

typedef struct sudoku_grid {
    SDL_Color thinBorderColor;
    SDL_Window *window;
    SDL_Surface *windowSurface;
    SDL_Renderer *renderer;
    SDL_Color hoverBackgroundColor;
    SDL_Color clickBackgroundColor;
    SDL_Color black;
    SDL_Color white;
    TTF_Font *font;
    cell *lastUpdated;
    cell* lastHovered;
} sudokuGrid;

void tryInitGridFont(sudokuGrid*);

int loadGrid(cell* [][9], char*, int);

sudokuGrid *initGrid(SDL_Window **, SDL_Surface **, SDL_Renderer **);

void drawSudokuGrid(sudokuGrid*);

#endif //SDL_SUDOKUGRID_H
