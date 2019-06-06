//
// Created by TheRolf on 03/05/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "sdl_sudoku.h"

extern sudokuGrid *data;
void updateHover(cell* position) {
    //Fonction permettant de mettre à jour la cellule en surbrillance

    if (data->lastHovered==NULL) { //Si la souris était précédemment hors de la grille
        if (position!=NULL) { //Si la cellule est actuellement dans la grille
            printHover(position); //Mets en surbrillance la cellule survolée (en terme graphique)
            position->isHovered = 1; //Mets en surbrillance la cellule survolée (en terme de donnée)
            data->lastHovered=position;
        }
    }
    else{ //Si la souris était précédemment dans la grille
        if (!data->lastHovered->isClicked) { //Si la cellule en surbrillance n'est pas sélectionnée
            if (position!=data->lastHovered) { //Si la souris ne survole pas la case en surbrillance
                if (position==NULL) { //Si la souris est hors de la grille
                    removeHover(data->lastHovered); //La cellule dernièrement en surbrillance ne l'est plus
                    data->lastHovered->isHovered=0;
                    data->lastHovered=position;
                }
                else{ //Si la souris est dans la grille
                    removeHover(data->lastHovered); //la cellule dernièrement en surbrillance ne l'est plus
                    data->lastHovered->isHovered=0;
                    printHover(position); //La cellule survolée passe en surbrillance
                    position->isHovered=1;
                    data->lastHovered=position;
                }
            }
        }
    }

}

void getMousePosition(cell **c,char click) {
    //Fonction permettant d'obtenir la postion de la souris

    int x, y;
    SDL_GetMouseState(&x, &y); //Obtention des coordonés

    if (x > GRID_MARGIN && x < GRID_MARGIN + GRID_SIZE && y > GRID_MARGIN && y < GRID_MARGIN + GRID_SIZE) { //Si la souris est dans la grille

        //Calcul de la cellule survolée
        int xcells = (x-(x>=381) - GRID_MARGIN)/(GRID_CELL_SIZE+1);
        int ycells = (y-(y>=381) - GRID_MARGIN)/(GRID_CELL_SIZE+1);
        *c = data->cells[xcells][ycells]; //Stockage dans une variable extérieur (contournement de la restriction d'une seule variable retournée par une fonction)
    }

    if (click && x > GRID_MARGIN + 5 && x < GRID_MARGIN + GRID_SIZE - 5 && y > GRID_MARGIN*2 + GRID_SIZE && y < GRID_MARGIN*2 + GRID_SIZE + GRID_CELL_SIZE) { //Si le joueur à cliqué dans la zone avec les restrictions affichée
        int l =  (x-GRID_MARGIN - 5)/GRID_CELL_SIZE + 1; //Calcul du nombre survolé
        *c = data->lastClicked; //Instruction permettant de ne pas déselectionner la cellule actuellement sélectionnée
        data->typedNumber = l; //Indication que le joueur à saisie le nombre survolé
    }
}
