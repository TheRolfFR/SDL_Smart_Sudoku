#include <stdio.h>
#include <SDL2/SDL.h>
#include "sdl_custom_lib.h"
#include "sudoku_lib/sdl_sudoku.h"
#ifndef CONST_MAIN
#define CONST_MAIN
#define FPS 60
#define TICKS_FPS 1000/FPS
#endif

int main(int argc, char **argv)
{
    sudokuGrid g;
    sudokuGrid *grid = &g;

    // on initialise la grille
    if(!initializeSudoku(grid))
        return -1;

    // on charge une grille random
    if(loadGrid(grid->cells, "../grids/", 2))
        return -1;

    //ton game controller j'ai pas compris
    gameController(grid);

    // on dessine la grille
    drawSudokuGrid(grid);

    // on dessine tous les chiffres de la grille
    int a, b;
    for(a = 0; a < 9; a++) {
        for(b = 0; b < 9; b++) {
            cell *c = grid->cells[a][b];
            updateNumberAtPosition(grid, c, 0, 0);
        }
    }

    // on dessine le fon des nombres?
    drawNumbersBackground(grid);

    // on affiche le rendu
    SDL_RenderPresent(grid->renderer);

    // le while sui tourne tout le temps
    int continuer = 1;
    SDL_Event event;
    while (continuer)
    {
        SDL_WaitEvent(&event);

        // add a timer here
        Uint32 tick = SDL_GetTicks();

        switch(event.type)
        {
            case SDL_QUIT: // on quitte
                continuer = 0;
                break;
            case SDL_MOUSEMOTION: // la souris bouge
                calculatePositionAndUpdate();
                break;
            case SDL_MOUSEBUTTONUP: // on "clique"
                // lol
                break;
        }

        if(event.type != SDL_QUIT) {
            SDL_RenderPresent(grid->renderer);
        }

        // the difference in ms determinating the grid
        Uint32 difference = SDL_GetTicks() - tick;

        // if time < refresh rate wait for the time
        printf("%u %u\n", difference, TICKS_FPS);
        if(difference < TICKS_FPS) {
            SDL_Delay(difference);
        }
    }

    // on détruit le rendu
    SDL_DestroyRenderer(grid->renderer);

    // on détruit la fenêtre etc bla bla bla
    destroyAndQuit(&grid->window);

    return 0;
}