#include <stdio.h>
#include <SDL2/SDL.h>
#include "sdl_custom_lib.h"
#include "sudoku_lib/sdl_sudoku.h"
#ifndef CONST_MAIN
#define CONST_MAIN
#endif

int main(int argc, char **argv)
{
    sudokuGrid g;
    sudokuGrid *grid = &g;

    // on initialise la grilles
    if(!initializeSudoku(grid))
        return -1;

    // on charge une grille random
    if(loadGrid(grid, "../grids/", 2))
        return -1;

    initRules(grid);

    // on dessine la grille
    drawSudokuGrid(grid);

    // on dessine tous les chiffres de la grille
    int a, b;
    for(a = 0; a < 9; a++) {
        for(b = 0; b < 9; b++) {
            cell *c = grid->cells[a][b];
            drawNumberAtPosition(grid, c);
        }
    }

    // on affiche le rendu
    SDL_RenderPresent(grid->renderer);

    //le jeu lorsqu'il est lancé
    gameController(grid);

    // on détruit le rendu
    SDL_DestroyRenderer(grid->renderer);

    // on détruit la fenêtre etc bla bla bla
    destroyAndQuit(&grid->window);

    return 0;
}