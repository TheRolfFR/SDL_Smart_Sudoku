//
// Created by TheRolf on 09/05/2019.
//

#include "sdl_sudoku.h"

extern sudokuGrid *data;
void updateCellValue() {
    //Fonction permettant de mettre à jour une cellule en fonction du nombre demandé

    int value = data->typedNumber; //Récuration du nombre demandé

    if (data->lastClicked != NULL && !data->lastClicked->isReadOnly) { //Si il y a une cellule modifiable sélectionnée
        if (data->lastClicked->rules[value-1]!=NULL) { //Si le nombre demandé est interdit
            if (data->redHover == value) { //Si les cellules empêchant la saisie du nombre demandé sont sur fond rouge
                hideRules(data->lastClicked->rules[value-1]); //Retrait des fonds rouge
            } else{ //Si les cellules empêchant la saisie du nombre demandé ne sont pas sur fond rouge
                if (data->redHover!=0) { //Si des cellules sont sur fond rouge
                    hideRules(data->lastClicked->rules[data->redHover-1]); //Retrait des fonds rouge
                }
                showRules(data->lastClicked->rules[value-1]); //Affichage d'un fond rouge sur les cellules empêchant la saisie du nombre demandé
                data->redHover = value; //Indication des cellules actuellement sur fond rouge
            }
        } else{ //Si le nombre demandé est autorisé
            if (!data->undoMode) { //Si le mode retour en arrière n'est pas activé
                addUndoStep(changeLastClicked,(data->lastClicked->line+1)*10+data->lastClicked->column+1); //Création d'une nouvelle étape dans la liste retour en arrière
            }
            if (data->pencilMarkMode) { //Si le mode annotation est activé
                if (data->lastClicked->number==EMPTY_VALUE) { //Si la cellule est vide
                    if (data->lastClicked->pencilMark[value-1]) { //Si l'annotation demandée est déjà présente
                        data->lastClicked->pencilMark[value-1] = 0; //Retrait de l'annotation (en terme de donnée)
                        removePencilMark(data->lastClicked,value); //retrait de l'annotation (en terme graphique)
                    }
                    else { //Si l'annotation demandée n'est pas présente
                        data->lastClicked->pencilMark[value-1] = 1; //Ajout de l'annotation (en terle de donnée)
                        drawPencilMark(data->lastClicked, value); //Ajout de l'annotation (en terme graphique)
                    }
                    if (!data->undoMode) { //Si le mode retour en arrière n'est pas activé
                        //Ajout, dans la liste retour en arrière, des instruction permettant d'annuler les actions effectuée
                        addUndoAction(changeMode,0);
                        addUndoAction(updateCellValue,value);
                        addUndoAction(changeMode,0);
                    }
                }
            }
            else { //Si le mode annotation n'est pas activé
                if (!data->undoMode) { //Si le mode retour en arrière n'est pas activé
                    addUndoAction(clearCell,0); //Ajout d'instruction dans la liste
                }
                if (data->lastClicked->number!=EMPTY_VALUE) { //Si la cellule n'est pas vide
                    if (!data->undoMode) { //Si le mode retour en arrière n'est pas activé
                        addUndoAction(updateCellValue,data->lastClicked->number); //Ajout d'instruction dans la liste
                    }
                    removeRules(); //Retrait des restrictions imposée par cette cellule
                }
                if (data->lastClicked->number!=EMPTY_VALUE || hasPencilMark(data->lastClicked)) { //Si la cellule contenait une valeur ou des annotations
                    drawNumberBackground(data->lastClicked); //Afficahge d'un fond blanc
                }
                if (hasPencilMark(data->lastClicked)) { //Si la cellule a des annotations
                    resetPencilMark(data->lastClicked); //Retrait des annotations
                }

                data->lastClicked->number = value; //Ajout de la valeur demandée

                addRules(); //Ajout des restrictions imposées par la valeur demandée

                drawNumberAtPosition(data->lastClicked); //Afficahge de la valeur demandée
            }
        }
    }
    data->typedNumber = 0; //Réinitialisation de la valeur demandée
}

void clearCell() {
    //Fonction vidant une cellule

    if (data->lastClicked->number!=EMPTY_VALUE) { //Si la cellule à une valeur
        if (!data->undoMode) { //Si le mode retour en arrière n'est pas activé
            addUndoStep(changeLastClicked,(data->lastClicked->line+1)*10+data->lastClicked->column+1); //Ajout d'une nouvelle étape
            addUndoAction(updateCellValue,data->lastClicked->number); //Ajout d'une instruction
        }
        removeRules(); //Retrait des restrictions imposées par la cellule
        data->lastClicked->number = EMPTY_VALUE; //Retrait de la valeur
        drawNumberBackground(data->lastClicked); //Affichage d'un fond blanc
    }
    if (hasPencilMark(data->lastClicked)) {
        if (!data->undoMode) { //Si le mode retour en arrière n'est pas activé
            addUndoStep(changeLastClicked,(data->lastClicked->line+1)*10+data->lastClicked->column+1); //Ajout d'une nouvelle étape
        }
        resetPencilMark(data->lastClicked); //Retrait des annotations
        drawNumberBackground(data->lastClicked); //Affichage d'un fond blanc
    }
}

void resetPencilMark(cell* current) {
    //Fonction retirant les annotations d'une cellule

    for (int i = 0; i < 9; i = i+1) { //Boucle parcourant les annotations possibles
        if (current->pencilMark[i]) { //Si la cellule possède l'annotation i+1
            if (!data->undoMode) { //Si le mode retour en arrière n'est pas activé
                //Ajout d'instructions
                addUndoAction(changeMode,0);
                addUndoAction(updateCellValue,i+1);
                addUndoAction(changeMode,0);
            }
            current->pencilMark[i] = 0; //Retrait de l'annotation
        }
    }
}