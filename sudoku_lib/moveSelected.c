//
// Created by TheRolf on 09/05/2019.
//

#include "moveSelected.h"

void moveSelected(sudokuGrid *data, int relativex, int relativey) {
    // recupérer le x et y dans la grille
    if(data->lastClicked != NULL) {
        // on calcule les supposés nouveaux x et y
        int newx = data->lastClicked->column + relativex;
        int newy = data->lastClicked->line + relativey;

        // on regarde si les index sont corrects sinon on les limite
        int x = (newx < 0) ? 8 : newx%9;
        int y = (newy < 0) ? 8 : newy%9;

        // on apelle la sélection de la nouvelle cellule
        selectCell(data, data->cells[y][x]);
    }
}
