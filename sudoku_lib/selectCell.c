//
// Created by asus on 09/05/2019.
//

#include "sdl_sudoku.h"


// fonction pour sélectionner la cellule
void selectCell(sudokuGrid* data, cell* position){
    if(position==NULL){ // rien n'est sélectionné
        if(data->lastHovered!=NULL){ // on enlève tout
            data->lastHovered->isClicked = 0;
            data->lastClicked = NULL;
            updateHover(data,position);
        }
    }
    else{
        if (position!=data->lastHovered){ // on sélectionne sur un élément différent de celui précédemment survolé (supposé impossible mais codé)
            data->lastHovered->isClicked = 0;
            updateHover(data,position);
            position->isClicked = 1;
            data->lastClicked = position;
        }
        else{ // on sélectionne l'élément survolé
            if(!position->isClicked){ // s'il n'est pas cliqué, on le met
                position->isClicked = 1;
                data->lastClicked = position;
            }
        } // on affiche les nombres disponibles pour la cellule
        drawAvailableNumbers(data);
    }
}

void unselect(sudokuGrid* data){  // on supprime tout
    data->lastHovered->isClicked = 0;
    updateHover(data,getMousePosition(data));
    SDL_Color lightgrey = {189,189,189};
    drawNumberButtonsBackground(data, &lightgrey); // on reaffiche la couleur de fond sur les anciens nombres disponibles
    data->lastClicked = NULL;
}