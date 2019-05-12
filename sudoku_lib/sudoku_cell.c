//
// Created by TheRolf on 03/05/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "sdl_sudoku.h"

// fonction d'initialisation de cellule lancée au début
cell *initCell(int l, int c, int number, char isHovered, char isClicked) {
    // on crée la cellule
    cell *myCell = malloc(sizeof(cell));

    // on met les champs avec leur valeur
    myCell->isHovered = isHovered;
    myCell->isClicked = isClicked;
    myCell->line = l;
    myCell->column = c;
    myCell->number = number;
    myCell->isReadOnly = (number != EMPTY_VALUE) ? 1 : 0; // on reconnait s'ils les nombres sont réécrivables selon la "valeur vide"

    // on initialise les champs des tableaux nuls
    int i;
    for(i = 0; i < 9; i++) {
        myCell->rules[i] = NULL;
        myCell->pencilMark[i] = 0;
    }

    // on retourne la cellule
    return myCell;
}

// fonction de debug pour voir la cellule
void printCell(cell *c) {
    printf("cell %p : ", c);
    if(c != NULL) {
        printf(" number : %d", c->number);
        printf(" line : %d", c->line);
        printf(" column : %d", c->column);
        printf(" isHovered : %d", c->isHovered);
        printf(" isReadOnly : %d\n", c->isReadOnly);
    }
}
