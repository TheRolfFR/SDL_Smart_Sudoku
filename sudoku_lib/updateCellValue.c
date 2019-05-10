//
// Created by TheRolf on 09/05/2019.
//

#include "updateCellValue.h"

void updateCellValue(sudokuGrid *data, int value) {
    printf("typing %d\n", value);
    if(data->lastClicked != NULL && !data->lastClicked->isReadOnly && data->lastClicked->rules[value-1]==NULL) {
        if (data->lastClicked->number!=EMPTY_VALUE){
            drawNumberBackground(data, data->lastClicked);
        }
        data->lastClicked->number = value;
        drawNumberAtPosition(data, data->lastClicked);
        updateRules(data);
    }
}

void updateRules(sudokuGrid* data){
    cell* current;
    cell* modified = data->lastClicked;
    int i;
    for(i = 0; i<=8; i = i+1){
        current = data->cells[i][modified->column];
        //erasePencilMark(data,current);
        if (current!=modified){
            //addElement(current->rules[modified->number], modified); //a faire
        }
    }
    for(i = 0; i<=8; i = i+1){
        current = data->cells[modified->line][i];
        //erasePencilMark(data,current);
        if (current!=modified){
            //addElement(current->rules[modified->number], modified); //a faire
        }
    }
    for(i = (modified->line%3==0); i<=2; i = i+1+(modified->line%3==i)){
        for (int j = (modified->column%3==0); j<=2; j+1+(modified->column%3==j)){
            current = data->cells[i][j];
            //erasePencilMark(data,current);
            //addElement(current->rules[modified->number], modified);
        }
    }
}