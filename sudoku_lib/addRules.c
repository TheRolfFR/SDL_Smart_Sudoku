//
// Created by asus on 10/05/2019.
//

#include "sdl_sudoku.h"

extern sudokuGrid *data;
void addRules(){
    cell* current; //Cellule en cours de traitement (déclarée pour simplifier l'écriture et la compréhension)
    cell* modified = data->lastClicked; //Cellule dernièrement modifiée par le joueur (déeclaré pour simplifier l'écriture et la compréhension)
    int i;

    for(i = 0; i<=8; i = i+1){ //Mise à jour des autorisation sur la colonne de la case modifiée
        current = data->cells[i][modified->column];
        if (current!=modified){ //Nous ne mettons pas à jour les autorisations de la case modifiée
            current->rules[modified->number-1] = addRule(current->rules[modified->number-1], modified); //Ajout de la cellule modifié comme "bloqueur" de la cellule en cours
            if(current->pencilMark[modified->number-1]){ //Si il y a une annotation correspondante à la valeur bloqué
                current->pencilMark[modified->number-1] = 0; //L'annotation est retirée
                removePencilMark(current,modified->number);
            }
        }
    }

    for(i = 0; i<=8; i = i+1){ //Mise à jour de la ligne (même fonctionnement que la colonne)
        current = data->cells[modified->line][i];
        if (current!=modified){
            current->rules[modified->number-1] = addRule(current->rules[modified->number-1], modified);
            if(current->pencilMark[modified->number-1]){
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
                current->pencilMark[modified->number-1] = 0;
                removePencilMark(current,modified->number);
            }
        }
    }
}