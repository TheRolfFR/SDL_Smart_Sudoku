//
// Created by asus on 08/05/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "sdl_sudoku.h"

#define FPS 60
#define TICKS_FPS 1000/FPS

extern sudokuGrid *data;
void gameController() {
    //Fonction s'occupant du fonctionnement du jeu

    int continuer = 1;
    SDL_Event event;
    cell *c = NULL;
    while (continuer) //Tant que continuer=1, le jeu continue
    {
        SDL_WaitEvent(&event); //Attente d'une action de la part du joueur

        Uint32 tick = SDL_GetTicks(); //Récupération du temps avant les calculs

        switch(event.type) //Différentiation des events
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEMOTION: //Mouvement de la souris
                getMousePosition(&c,0); //Obtention de la position de la souris
                updateHover(c); //Mise à jour de la cellule en surbrillance
                break;
            case SDL_MOUSEBUTTONUP: //Clique de la souris
                data->lastKeyWasCtrl = 0;
                getMousePosition(&c,1); //Obtention de la position de la souris
                selectCell(c); //Selection de la cellule
                if (data->typedNumber != 0) { //Si la position est un des 9 nombres
                    updateCellValue(); //Mets à jour la cellule
                }
                continuer = handleDifficultyButtons(); //Test de la selection de difficulté
                break;
            case SDL_KEYDOWN: //Appui clavier
                keyInterpretor(event.key.keysym.sym); //Interprétation de la touche appuyée
        }

        c = NULL;


        if (isFinished() == 1) { //Si la grille est complétée
            win(); //Message de victoire
            continuer = 0; //Arrêt du jeu
        }

        if (event.type != SDL_QUIT) { //Si l'évènement est différent de quitter
            SDL_RenderPresent(data->renderer); //Rafraichissement du rendu
        }

        Uint32 difference = SDL_GetTicks() - tick; //Obtention du temps d'exécution


        if (difference < TICKS_FPS) { //Si le temps est inférieur à la durée d'un "tick"
            SDL_Delay(difference); //Pause du jeu afin de compléter le "tick"
        }
    }
}

int isFinished() {
    //Fonction indiquant qi la grille est finie

    int finished = 1, i = 0, j = 0;

    while (finished == 1 && j != 9) { //Boucle parcourant la grille
        if (data->cells[i][j]->number == EMPTY_VALUE) { //Si la cellule est vide
            finished = 0; //Le jeu n'est pas fini
        }
        else{ //Si la cellule n'est pas vide
            if (i != 8) { //Si la colonne n'est pas terminée
                i = i + 1; //Incrémentation
            }
            else{ //Si la colonne est terminée
                j = j + 1; //Passage à la suivante
                i = 0;
            }
        }
    }
    return finished;
}