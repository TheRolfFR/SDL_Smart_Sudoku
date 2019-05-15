//
// Created by asus on 09/05/2019.
//

#include "sdl_sudoku.h"


//Selection d'une cellule
void selectCell(sudokuGrid* data, cell* position){
    if(position==NULL){ //Souris hors de la grille
        if(data->lastHovered!=NULL){ //Si une cellule était sélectionnée
            data->lastHovered->isClicked = 0; //Désélection
            data->lastClicked = NULL;
            updateHover(data,position); //Mise à jour du "Hover"
        }
    }
    else{ //Souris dans la grille
        if (position!=data->lastHovered){ //Position différente de la cellule en surbrillance(hover)
            data->lastHovered->isClicked = 0; //Déselection de la précédente
            updateHover(data,position); //Déplacer le "Hover" sur la cellule actuelle
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

void unselect(sudokuGrid* data){  // Déselection de la cellule actuellement sélectionnée
    data->lastHovered->isClicked = 0;
    updateHover(data,getMousePosition(data)); //Mise à jour du "Hover"
    SDL_Color lightgrey = {189,189,189};
    drawNumberButtonsBackground(data, &lightgrey); // on reaffiche la couleur de fond sur les anciens nombres disponibles
    data->lastClicked = NULL;
}