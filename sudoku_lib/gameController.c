//
// Created by asus on 08/05/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "sdl_sudoku.h"

#define FPS 60
#define TICKS_FPS 1000/FPS

void gameController(sudokuGrid* data){


    int continuer = 1;
    SDL_Event event;
    while (continuer) //boucle du jeu
    {
        SDL_WaitEvent(&event);

        // le timer
        Uint32 tick = SDL_GetTicks();

        switch(event.type)
        {
            case SDL_QUIT: // on quitte
                continuer = 0;
                break;
            case SDL_MOUSEMOTION: // mouvement de souris
                 updateHover(data, getMousePosition(data));
                break;
            case SDL_MOUSEBUTTONUP: // clique souris
                selectCell(data, getMousePosition(data));
                break;
            case SDL_KEYDOWN: // appui clavier
                keyInterpretor(data,event.key.keysym.sym);
        }

        // si l'évènement est différent de quitter on rafraichit le rendu
        if(event.type != SDL_QUIT) {
            SDL_RenderPresent(data->renderer);
        }

        if(data->emptyCell==0){ //si toute les cases sont remplis
            //win(); //message de victoire
            continuer = 0;
        }

        // avoir le temps d'éxécution
        Uint32 difference = SDL_GetTicks() - tick;

        // si le temps est inférieur aux ticks on pause le jeu
        // printf("%u %u\n", difference, TICKS_FPS); //debug
        if(difference < TICKS_FPS) {
            SDL_Delay(difference);
        }
    }
}
