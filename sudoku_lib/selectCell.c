//
// Created by asus on 09/05/2019.
//

#include "sdl_sudoku.h"


extern sudokuGrid *data;
//Selection d'une cellule
void selectCell(cell* position){
    if(position==NULL){ //Souris hors de la grille
        if(data->lastHovered!=NULL){ //Si une cellule était sélectionnée
            if(data->redHover!=0){
                hideRules(data->lastClicked->rules[data->redHover-1]);
            }
            data->lastHovered->isClicked = 0; //Désélection
            data->lastClicked = NULL;
            updateHover(position); //Mise à jour du "Hover"

            SDL_Color lightgrey = {189,189,189};
            drawNumberButtonsBackground(&lightgrey); // on reaffiche la couleur de fond sur les anciens nombres disponibles
        }
    }
    else{ //Souris dans la grille
        if (position!=data->lastHovered){ //Position différente de la cellule en surbrillance(hover)
            if(data->redHover!=0){
                hideRules(data->lastClicked->rules[data->redHover-1]);
            }
            data->lastHovered->isClicked = 0; //Déselection de la précédente
            updateHover(position); //Déplacer le "Hover" sur la cellule actuelle
            position->isClicked = 1; //Sélectionner la nouvelle cellule
            data->lastClicked = position;
        }
        else{ //Souris sur la case en surbrillance
            if(!position->isClicked){ //Cellule actuelle non sélectionnée
                position->isClicked = 1; //Sélection
                data->lastClicked = position;
            }
        } // on affiche les nombres disponibles pour la cellule
        drawAvailableNumbers(data);
    }
}

void unselect(){  // Déselection de la cellule actuellement sélectionnée
    if(data->redHover!=0){
        hideRules(data->lastClicked->rules[data->redHover-1]);
    }
    data->lastHovered->isClicked = 0;
    cell *c;
    getMousePosition(&c, NULL);
    updateHover(c); //Mise à jour du "Hover"

    SDL_Color lightgrey = {189,189,189};
    drawNumberButtonsBackground(&lightgrey); // on reaffiche la couleur de fond sur les anciens nombres disponibles
    data->lastClicked = NULL;
}