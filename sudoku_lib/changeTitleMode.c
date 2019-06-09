//
// Created by TheRolf on 10/05/2019.
//

#include "sdl_sudoku.h"
#include <string.h>

extern sudokuGrid *data;

void ChangeTitleMode() {
    //Fonction permettant d'indiquer l'activation de mode annotation via le titre de la fenêtre

    char title[TAILLE_MAX];
    strcpy(title, data->initialTitle); //Copie du titre original
    strcat(title, (data->pencilMarkMode) ? " (Pencil Mark)" : ""); //Ajout de la mention (Pencil Mark) dépendant du mode
    SDL_SetWindowTitle(data->window, title); //Mise à jour du titre
}