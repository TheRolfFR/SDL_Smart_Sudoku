//
// Created by TheRolf on 09/05/2019.
//

#include "updateCellValue.h"

void updateCellValue(sudokuGrid *data, int value) {
    if(data->lastClicked != NULL && !data->lastClicked->isReadOnly && data->lastClicked->rules[value-1]==NULL) {
        if(data->pencilMarkMode) {
            if(data->lastClicked->pencilMark[value-1]){
                data->lastClicked->pencilMark[value-1] = 0;
                //removePencilMark(data->lastClicked,value);
            }
            else{
                data->lastClicked->pencilMark[value-1] = 1;
                drawPencilMark(data, data->lastClicked);
            }
        }
        else {
            // mode nombre normal
            if (data->lastClicked->number!=EMPTY_VALUE){
                removeRules(data);
                drawNumberBackground(data, data->lastClicked);
            }
            data->lastClicked->number = value;
            addRules(data);
            drawNumberAtPosition(data, data->lastClicked);
        }
    }
}

void clearCell(sudokuGrid* data){
    if(data->lastClicked->number!=EMPTY_VALUE){
        removeRules(data);
        data->lastClicked->number = EMPTY_VALUE;
    }
    else {
        resetPencilMark(data->lastClicked);
    }
    drawNumberBackground(data,data->lastClicked);
}

void resetPencilMark(cell* current){
    for (int i = 0; i < 9; i = i+1) {
        current->pencilMark[i] = 0;
    }
}