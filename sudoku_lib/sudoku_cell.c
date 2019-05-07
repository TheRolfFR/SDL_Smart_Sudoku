//
// Created by TheRolf on 03/05/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "sdl_sudoku.h"

cell *initCell(int l, int c, int number, char isHovered, char isClicked) {
    cell *myCell = malloc(sizeof(cell));
    myCell->isHovered = isHovered;
    myCell->isClicked = isClicked;
    myCell->line = l;
    myCell->column = c;
    myCell->number = number;
}

void printCell(cell *c) {
    printf("cell %p : ", c);
    printf(" number : %d", c->number);
    printf(" line : %d", c->line);
    printf(" column : %d", c->column);
    printf(" isHovered : %d\n", c->isHovered);
}
