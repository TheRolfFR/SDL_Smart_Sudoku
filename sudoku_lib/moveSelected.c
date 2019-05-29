//
// Created by TheRolf on 09/05/2019.
//

#include "moveSelected.h"

extern sudokuGrid *data;
void moveSelected(int relativex, int relativey) {
    //Fonction permettant de changer de cellule sélectionnée via les flèches directionnelles

    if(data->lastClicked != NULL) { //Si il y a une cellule sélectionnée

        //Calcul coordonnées de la nouvelle cellule sélectionnée
        int newx = data->lastClicked->column + relativex;
        int newy = data->lastClicked->line + relativey;

        //Rectification en cas de sortie de grille (sortir de la grille par la gauche nous positionne à droite et inversement)
        int x = (newx < 0) ? 8 : newx%9;
        int y = (newy < 0) ? 8 : newy%9;

        selectCell(data->cells[y][x]); //Sélection de la nouvelle cellule
    }
}
