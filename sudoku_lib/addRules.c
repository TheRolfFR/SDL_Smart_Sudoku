//
// Created by asus on 10/05/2019.
//

#include "sdl_sudoku.h"

extern sudokuGrid *data;
void addRules(){
    //Fonction mettant à jour les restrictions après le dernier changements sur la grille

    if(!data->undoMode){ //ajout d'un changement de mode dans la liste "undo" (les modifications ici ne concernent que les annotations)
        addUndoAction(changeMode,0);
    }
    cell* current; //Cellule en cours de traitement (déclarée pour simplifier l'écriture et la compréhension)
    cell* modified = data->lastClicked; //Cellule dernièrement modifiée par le joueur (déeclaré pour simplifier l'écriture et la compréhension)
    int i;

    for(i = 0; i<=8; i = i+1){ //Mise à jour des restrictions sur la colonne de la case modifiée
        current = data->cells[i][modified->column];
        if (current!=modified){ //Nous ne mettons pas à jour les restrictions de la case modifiée
            current->rules[modified->number-1] = addRule(current->rules[modified->number-1], modified); //Ajout de la cellule modifiée comme restriction de la cellule en cours de traitement
            if(current->pencilMark[modified->number-1]){ //Si il y a une annotation correspondant à la valeur restreinte
                if(!data->undoMode){ //Si nous ne somme pas en train d'annuler des actions
                    addUndoAction(changeLastClicked,(current->line+1)*10+current->column+1); //ajout des actions contraires à la liste "undo"
                    addUndoAction(updateCellValue,modified->number);
                }
                current->pencilMark[modified->number-1] = 0; //Retrait de l'annotation (en terme de donnée)
                removePencilMark(current,modified->number); //Retrait de l'annotation (en terme graphique)
            }
        }
    }

    for(i = 0; i<=8; i = i+1){ //Mise à jour de la ligne (même fonctionnement que la colonne)
        current = data->cells[modified->line][i];
        if (current!=modified){
            current->rules[modified->number-1] = addRule(current->rules[modified->number-1], modified);
            if(current->pencilMark[modified->number-1]){
                if(!data->undoMode){
                    addUndoAction(changeLastClicked,(current->line+1)*10+current->column+1);
                    addUndoAction(updateCellValue,modified->number);
                }
                current->pencilMark[modified->number-1] = 0;
                removePencilMark(current,modified->number);
            }
        }
    }
    int j;
    for(i = (modified->line%3==0); i<=2; i = i+1+(modified->line%3-1==i)){ //Mise à jour de la région (les conditions booléennes permettent d'éviter les cases déjà mise à jour)
        for (j = (modified->column%3==0); j<=2; j = j+1+(modified->column%3-1==j)){
            current = data->cells[i+modified->line-modified->line%3][j+modified->column-modified->column%3];
            current->rules[modified->number-1] = addRule(current->rules[modified->number-1], modified);
            if(current->pencilMark[modified->number-1]){
                if(!data->undoMode){
                    addUndoAction(changeLastClicked,(current->line+1)*10+current->column+1);
                    addUndoAction(updateCellValue,modified->number);
                }
                current->pencilMark[modified->number-1] = 0;
                removePencilMark(current,modified->number);
            }
        }
    }
    if(!data->undoMode){ //retour en mode normal dans la list undo
        addUndoAction(changeMode,0);
    }
}