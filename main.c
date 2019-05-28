#include <stdio.h>
#include <SDL2/SDL.h>
#include "sdl_custom_lib.h"
#include "sudoku_lib/sdl_sudoku.h"
#ifndef CONST_MAIN
#define CONST_MAIN
#endif

sudokuGrid *data;
SDL_Color SDL_white = {255, 255, 255};
SDL_Color SDL_black = {0, 0, 0};
SDL_Color SDL_blue = {0x4D, 0xD0, 0xE1};
SDL_Color SDL_lightgrey = {189,189,189};
SDL_Color SDL_grey = {0x37, 0x47, 0x4F}; // #37474F
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

    data->undoMode = 0;

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

    // clear memory
    freeMemory();

    return 0;
}