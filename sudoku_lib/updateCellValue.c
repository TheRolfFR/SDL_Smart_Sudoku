//
// Created by TheRolf on 09/05/2019.
//

#include "sdl_sudoku.h"

// fonction qui met à jour la cellule en fonction d'une touche numérique tapée
void updateCellValue(sudokuGrid *data, int value) {
    // si une case a été clique est qu'elle est modifiable et qu'elle n'est pas bloquée
    if(data->lastClicked != NULL && !data->lastClicked->isReadOnly && data->lastClicked->rules[value-1]==NULL) {
        // si on est en mode pencilmark
        if(data->pencilMarkMode) {
            // si la case était vide précédemment (empeche d'écrire des pencils marks sur les nombres)
            if(data->lastClicked->number==EMPTY_VALUE){
                // si la pencil mark du nombre existait déjà, on l'enlève
                if(data->lastClicked->pencilMark[value-1]){
                    data->lastClicked->pencilMark[value-1] = 0;
                    removePencilMark(data, data->lastClicked,value);
                }
                else { // sinon on l'ajoute
                    data->lastClicked->pencilMark[value-1] = 1;
                    drawPencilMark(data, data->lastClicked, value);
                }
            }
        }
        else {
            // si on est en mode nombre normal
            if(data->lastClicked->number!=EMPTY_VALUE) {
                // on enlève les règles
                removeRules(data);
            }
            // si l'y avait quelque-chose avant, on redessine un fond
            if (data->lastClicked->number!=EMPTY_VALUE || hasPencilMark(data->lastClicked)){
                drawNumberBackground(data, data->lastClicked);
            }

            // on met à jour la valeur
            data->lastClicked->number = value;

            // on rajoute les restrictions aux cases concernées
            addRules(data);

            // on dessine le nombre en question
            drawNumberAtPosition(data, data->lastClicked);
        }
    }
}

// fonction qui nettoie les cellules
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

// fonction qui réinitialise les pencil marks
void resetPencilMark(cell* current){
    for (int i = 0; i < 9; i = i+1) {
        current->pencilMark[i] = 0;
    }
}