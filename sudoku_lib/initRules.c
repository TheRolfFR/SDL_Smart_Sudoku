//
// Created by asus on 11/05/2019.
//

#include "sdl_sudoku.h"

// on ajoute les rules au lancement de la grid
void initRules(sudokuGrid* data){
    int i,j;
    for (i = 0; i<=8; i = i+1){
        for (j = 0; j <=8 ; j = j+1) {
            if(data->cells[i][j]->isReadOnly){
                data->lastClicked = data->cells[i][j]; // petit trick pour la fonction suivante
                addRules(data); // et cela pour chaque cellule
            }
        }
    }
    data->lastClicked = NULL;
}