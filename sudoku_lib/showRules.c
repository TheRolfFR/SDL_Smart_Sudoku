//
// Created by asus on 23/05/2019.
//

#include "sdl_sudoku.h"

extern sudokuGrid* data;
void showRules(cellList* currentElement){
    while(currentElement!=NULL){
        printRed(currentElement->bloqueur);
        currentElement = currentElement->next;
    }
}

void hideRules(cellList* currentElement){
    while(currentElement!=NULL){
        drawNumberBackground(currentElement->bloqueur);
        drawNumberAtPosition(currentElement->bloqueur);
        currentElement = currentElement->next;
    }
    data->redHover = 0;
}