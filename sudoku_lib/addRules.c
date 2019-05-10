//
// Created by asus on 10/05/2019.
//

#include "sdl_sudoku.h"

void addRules(sudokuGrid* data){
    cell* current;
    cell* modified = data->lastClicked;
    int i;

    for(i = 0; i<=8; i = i+1){
        current = data->cells[i][modified->column];
        if (current!=modified){
            current->rules[modified->number-1] = addRule(current->rules[modified->number-1], modified); //a faire
            if(current->pencilMark[modified->number-1]){
                current->pencilMark[modified->number-1] = 0;
                //removePencilMark(current,modified->number);
            }
        }
    }

    for(i = 0; i<=8; i = i+1){
        current = data->cells[modified->line][i];
        if (current!=modified){
            current->rules[modified->number-1] = addRule(current->rules[modified->number-1], modified); //a faire
            if(current->pencilMark[modified->number-1]){
                current->pencilMark[modified->number-1] = 0;
                //removePencilMark(current,modified->number);
            }
        }
    }

    for(i = (modified->line%3==0); i<=2; i = i+1+(modified->line%3-1==i)){
        int j;
        for (j = (modified->column%3==0); j<=2; j=j+1+(modified->column%3-1==j)){
            current = data->cells[i+modified->line/3][j+modified->column/3];
            current->rules[modified->number-1] = addRule(current->rules[modified->number], modified);
            if(current->pencilMark[modified->number-1]){
                current->pencilMark[modified->number-1] = 0;
                //removePencilMark(current,modified->number);
            }
        }
    }
}