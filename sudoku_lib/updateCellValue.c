//
// Created by TheRolf on 09/05/2019.
//

#include "updateCellValue.h"

void updateCellValue(sudokuGrid *data, int value) {
    if(data->lastClicked != NULL && !data->lastClicked->isReadOnly) {
        data->lastClicked->number = value;
        drawNumberBackground(data, data->lastClicked);
    }
}