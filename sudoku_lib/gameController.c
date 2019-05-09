//
// Created by asus on 08/05/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "gameController.h"

#define FPS 60
#define TICKS_FPS 1000/FPS

void gameController(sudokuGrid* data){

    // le while sui tourne tout le temps
    int continuer = 1;
    SDL_Event event;
    while (continuer)
    {
        SDL_WaitEvent(&event);

        // le timer
        Uint32 tick = SDL_GetTicks();

        switch(event.type)
        {
            case SDL_QUIT: // on quitte
                continuer = 0;
                break;
            case SDL_MOUSEMOTION: // la souris bouge
                 updateHover(data, getMousePosition(data));
                break;
            case SDL_MOUSEBUTTONUP: // on "clique"
                // lol
                break;
        }

        if(event.type != SDL_QUIT) {
            SDL_RenderPresent(data->renderer);
        }

        // avoir le temps d'éxécution
        Uint32 difference = SDL_GetTicks() - tick;

        // si le temps est inférieur aux ticks on pause le jeu
        printf("%u %u\n", difference, TICKS_FPS);
        if(difference < TICKS_FPS) {
            SDL_Delay(difference);
        }
    }
}
