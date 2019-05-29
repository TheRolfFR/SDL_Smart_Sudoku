//
// Created by asus on 11/05/2019.
//

#include "sdl_sudoku.h"

extern sudokuGrid *data;
void initRules(){
    //Fonction permettant d'initialiser les restrictions imposées par les donnée de base

    int i,j;
    for (i = 0; i<=8; i = i+1){ //Boucles parcourant la grille
        for (j = 0; j <=8 ; j = j+1) {
            if(data->cells[i][j]->isReadOnly){ //Si la cellule est une donnée de base
                data->lastClicked = data->cells[i][j]; //Sélection de cette cellule (prérequis pour addRules)
                addRules(data); //Ajout des restrictions
            }
        }
    }
    data->lastClicked = NULL; //Réinitialisation de la dernière sélectionnée
}