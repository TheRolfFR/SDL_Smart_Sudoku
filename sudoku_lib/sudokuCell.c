//
// Created by TheRolf on 03/05/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "sdl_sudoku.h"

cell *initCell(int l, int c, int number, char isHovered, char isClicked) {
    //Fonction permettant de créer une cellule

    cell *myCell = malloc(sizeof(cell)); //Allocation de la mémoire

    //Initialisation des champs
    myCell->isHovered = isHovered; //Champs indiquant si la cellule est en surbrillance
    myCell->isClicked = isClicked; //Champs indiquant si la cellule est sélectionnée
    myCell->line = l; //Champs indiquant la ligne (en C) de la cellule
    myCell->column = c; //Champs indiquant la colonne (en C) de la cellule
    myCell->number = number; //Champs indiquant la valeur de la cellule
    myCell->isReadOnly = (number != EMPTY_VALUE) ? 1 : 0; //Champs indiquant si une cellule est une donnée de base


    int i;
    for(i = 0; i < 9; i++) {
        myCell->rules[i] = NULL; //Initialisation des listes des restrictions
        myCell->pencilMark[i] = 0; //Initialisation des indicateurs d'annotation
    }

    return myCell;
}

