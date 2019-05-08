#include <stdio.h>
#include <SDL2/SDL.h>
#include "sdl_custom_lib.h"
#include "sudoku_lib/sdl_sudoku.h"
#include "sudoku_lib/gameController.h"
#ifndef CONST_MAIN
#define CONST_MAIN
#define FPS 60
#define TICKS_FPS 1000/FPS
#endif

int main(int argc, char **argv)
{
    // cette fonction n existe pas encore
    // initializeSudoku(); //afficher la grille mais pas les nombres (ça se fera lors du choix de difficulté)

    SDL_Window *window = NULL;
    SDL_Surface *windowSurface = NULL;
    SDL_Renderer *renderer = NULL;

    int windowSide = 600;

    if(!init(&window, &windowSurface, &renderer, windowSide, windowSide)) {
        printf("Failed to initialize!");
        return -1;
    }

    // first draw
    sudokuGrid* grid = initGrid(&window, &windowSurface, &renderer);

    int result = loadGrid(grid->cells, "../grids/", 2);
    if(result != 0)
        return result;

    gameController(grid);

    drawSudokuGrid(grid);
    int a, b;
    for(a = 0; a < 9; a++) {
        for(b = 0; b < 9; b++) {
            cell *c = grid->cells[a][b];

            if(c != NULL) {
                updateNumberAtPosition(grid, c, 0, 0);
            }
        }
    }
    drawNumbersBackground(grid);

    SDL_RenderPresent(renderer);

    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);

        // add a timer here
        Uint32 tick = SDL_GetTicks();

        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEMOTION:
                calculatePositionAndUpdate();
                break;
            case SDL_MOUSEBUTTONUP:
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

    SDL_DestroyRenderer(renderer);

    destroyAndQuit(&window);

    return 0;
}