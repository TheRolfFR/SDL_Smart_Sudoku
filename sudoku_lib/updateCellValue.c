//
// Created by TheRolf on 09/05/2019.
//

#include "sdl_sudoku.h"

extern sudokuGrid *data;
// fonction qui met à jour la cellule en fonction d'une touche numérique tapée
void updateCellValue() {
    int value = data->typedNumber;
    // si une case a été clique et qu'elle est modifiable et qu'elle n'est pas bloquée
    if(data->lastClicked != NULL && !data->lastClicked->isReadOnly) {
        if(data->lastClicked->rules[value-1]!=NULL){
            if (data->redHover == value){
                hideRules(data->lastClicked->rules[value-1]);
            } else{
                if(data->redHover!=0){
                    hideRules(data->lastClicked->rules[data->redHover-1]);
                }
                showRules(data->lastClicked->rules[value-1]);
                data->redHover = value;
            }
        } else{
            // si on est en mode pencilmark
            if(data->pencilMarkMode) {
                // si la case était vide précédemment (empeche d'écrire des pencils marks sur les nombres)
                if(data->lastClicked->number==EMPTY_VALUE){
                    // si la pencil mark du nombre existait déjà, on l'enlève
                    if(data->lastClicked->pencilMark[value-1]){
                        data->lastClicked->pencilMark[value-1] = 0;
                        removePencilMark(data->lastClicked,value);
                    }
                    else { // sinon on l'ajoute
                        data->lastClicked->pencilMark[value-1] = 1;
                        drawPencilMark(data->lastClicked, value);
                    }
                }
            }
            else {
                // si on est en mode nombre normal
                if(data->lastClicked->number!=EMPTY_VALUE) { //La case conntient une valeur
                    //retrait des restrictions concernant cette valeur
                    removeRules();
                }
                // si l'y avait quelque-chose avant, on redessine un fond
                if (data->lastClicked->number!=EMPTY_VALUE || hasPencilMark(data->lastClicked)){
                    drawNumberBackground(data->lastClicked);
                }

                //Mise à jour de la valeur
                data->lastClicked->number = value;

                //Ajout des restrictions concernat la nouvelle valeur
                addRules(data);

                //Dessin du nombre en question
                drawNumberAtPosition(data->lastClicked);
            }
        }

    }
    data->typedNumber = 0;
}

// fonction qui nettoie les cellules
void clearCell(){
    if(data->lastClicked->number!=EMPTY_VALUE){ //Si la cellule à une valeur
        removeRules(); //Retire les restrictions
        data->lastClicked->number = EMPTY_VALUE; //Retire la valeur
    }
    else { //Si la cellule n'a pas de valeur
        resetPencilMark(data->lastClicked); //retire les annotations
    }
    drawNumberBackground(data->lastClicked);
}

// fonction qui réinitialise les pencil marks
void resetPencilMark(cell* current){
    for (int i = 0; i < 9; i = i+1) {
        current->pencilMark[i] = 0;
    }
}