#include <stdio.h>
#include <SDL2/SDL.h>
#include "sdl_custom_lib.h"
#include "sudoku_lib/sdl_sudoku.h"
#ifndef CONST_MAIN
#define CONST_MAIN
#endif

sudokuGrid *data;
int main(int argc, char **argv)
{
    sudokuGrid g;
    data = &g;

    // on initialise la grilles
    if(!initializeSudoku())
        return -1;

    // on charge une grille random
    if(loadGrid("../grids/", 2))
        return -1;

    initRules();

    // on dessine la grille
    drawSudokuGrid();

    // on dessine tous les chiffres de la grille
    int a, b;
    for(a = 0; a < 9; a++) {
        for(b = 0; b < 9; b++) {
            cell *c = data->cells[a][b];
            drawNumberAtPosition(c);
        }
    }

    // on affiche le rendu
    SDL_RenderPresent(data->renderer);

    //le jeu lorsqu'il est lancé
    gameController();

    // on détruit le rendu
    SDL_DestroyRenderer(data->renderer);

    // on détruit la fenêtre etc
    destroyAndQuit(&data->window);

    return 0;
}