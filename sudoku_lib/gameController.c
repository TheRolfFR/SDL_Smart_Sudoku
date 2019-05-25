//
// Created by asus on 08/05/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "sdl_sudoku.h"

#define FPS 60
#define TICKS_FPS 1000/FPS

extern sudokuGrid *data;
void gameController(){


    int continuer = 1;
    SDL_Event event;
    cell *c = NULL;
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
                getMousePosition(&c,0);
                updateHover(c);
                break;
            case SDL_MOUSEBUTTONUP: // clique souris
                data->lastKeyWasCtrl = 0;
                getMousePosition(&c,1);
                if(c != NULL) {
                    selectCell(c);
                } else if(data->typedNumber != 0) {
                    updateCellValue();
                }
                break;
            case SDL_KEYDOWN: // appui clavier
                keyInterpretor(event.key.keysym.sym);
        }

        c = NULL;

        // nombre de cellules vide nul
        if(data->emptyCell==0){ //Si il n'y a aucun cellule vide
            win(); //Message de victoire
            continuer = 0;
        }

        // si l'évènement est différent de quitter on rafraichit le rendu
        if(event.type != SDL_QUIT) {
            SDL_RenderPresent(data->renderer);
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
