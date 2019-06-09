//
// Created by TheRolf on 10/05/2019.
//

#include "sdl_sudoku.h"

extern sudokuGrid* data;
void initRules() {
    //Fonction permettant d'initialiser les restrictions imposées par les donnée de base

    int i,j;
    for (i = 0; i<=8; i = i+1) { //Boucles parcourant la grille
        for (j = 0; j <=8 ; j = j+1) {
            if (data->cells[i][j]->isReadOnly) { //Si la cellule est une donnée de base
                data->lastClicked = data->cells[i][j]; //Sélection de cette cellule (prérequis pour addRules)
                addRules(data); //Ajout des restrictions
            }
        }
    }
    data->lastClicked = NULL; //Réinitialisation de la dernière sélectionnée
    data->undoMode = 0; //Désactivation du mode retour en arrière (Précédemment activé pour ne pas enregistrer l'initialisation de restrictions comme actions du joueur)
}

cellList* addRule(cellList *list, cell *cellToAdd) {
    //Fonction permettant d'ajouter un élément en tête de liste chainée

    //Création de l'élément
    cellList *newHead = malloc(sizeof(cellList));
    newHead->bloqueur = cellToAdd;

    if (list != NULL) { //Si la liste n'est pas vide
        newHead->next = list; //Ajout de la liste derrière la nouvelle tête
    } else { //Si la liste est vide
        newHead->next = NULL; //Indique que la nouvelle tête est le dernier élément de la liste
    }

    return newHead; //Envois du pointeur de la nouvelle tête de liste
}

cellList *removeRule(cellList *list, cell *cellToRemove) {
    //Fonction permettant de supprimer un élément d'une liste chainée

    if (list == NULL) { //Si la liste est vide
        return NULL; //Aucune action n'est effectuée
    } else { //Si la liste n'est pas vide
        cellList *precedent = NULL;
        cellList *actuel = list;
        while (actuel != NULL && actuel->bloqueur != cellToRemove) { //Boucle recherchant l'élément à supprimer
            precedent = actuel;
            actuel = actuel->next;
        }

        if (actuel != NULL) { //Si l'élément a été trouvé
            if (precedent == NULL) { //Si l'élémet trouvé et le premier de la liste
                cellList *newHead = actuel->next; //Suppression de l'élément
                free(actuel); //Libération de la mémoire
                return newHead;
            } else { //Si l'élément trouvé n'est pas le premier
                precedent->next = actuel->next; //Suppression de la liste
                free(actuel); //Libération de la mémoire
                return list;
            }
        } else { //Si l'élément n'a pas été trouvé
            return list; //Aucune action effectuée
        }
    }
}

void addRules() {
    //Fonction permmettant d'ajouter les restrictions imposées par la cellules sélectionnée

    if (!data->undoMode) { //ajout d'un changement de mode dans la liste "undo" (les modifications ici ne concernent que les annotations)
        addUndoAction(changeMode,0);
    }
    cell* current; //Cellule en cours de traitement (déclarée pour simplifier l'écriture et la compréhension)
    cell* modified = data->lastClicked; //Cellule dernièrement modifiée par le joueur (déeclaré pour simplifier l'écriture et la compréhension)
    int i;

    for (i = 0; i<=8; i = i+1) { //Mise à jour des restrictions sur la colonne de la case modifiée
        current = data->cells[i][modified->column];
        if (current!=modified) { //Nous ne mettons pas à jour les restrictions de la case modifiée
            current->rules[modified->number-1] = addRule(current->rules[modified->number-1], modified); //Ajout de la cellule modifiée comme restriction de la cellule en cours de traitement
            if (current->pencilMark[modified->number-1]) { //Si il y a une annotation correspondant à la valeur restreinte
                if (!data->undoMode) { //Si nous ne somme pas en train d'annuler des actions
                    addUndoAction(changeLastClicked,(current->line+1)*10+current->column+1); //ajout des actions contraires à la liste "undo"
                    addUndoAction(updateCellValue,modified->number);
                }
                current->pencilMark[modified->number-1] = 0; //Retrait de l'annotation (en terme de donnée)
                removePencilMark(current,modified->number); //Retrait de l'annotation (en terme graphique)
            }
        }
    }

    for (i = 0; i<=8; i = i+1) { //Mise à jour de la ligne (même fonctionnement que la colonne)
        current = data->cells[modified->line][i];
        if (current!=modified) {
            current->rules[modified->number-1] = addRule(current->rules[modified->number-1], modified);
            if (current->pencilMark[modified->number-1]) {
                if (!data->undoMode) {
                    addUndoAction(changeLastClicked,(current->line+1)*10+current->column+1);
                    addUndoAction(updateCellValue,modified->number);
                }
                current->pencilMark[modified->number-1] = 0;
                removePencilMark(current,modified->number);
            }
        }
    }
    int j;
    for (i = (modified->line%3==0); i<=2; i = i+1+(modified->line%3-1==i)) { //Mise à jour de la région (les conditions booléennes permettent d'éviter les cases déjà mise à jour)
        for (j = (modified->column%3==0); j<=2; j = j+1+(modified->column%3-1==j)) {
            current = data->cells[i+modified->line-modified->line%3][j+modified->column-modified->column%3];
            current->rules[modified->number-1] = addRule(current->rules[modified->number-1], modified);
            if (current->pencilMark[modified->number-1]) {
                if (!data->undoMode) {
                    addUndoAction(changeLastClicked,(current->line+1)*10+current->column+1);
                    addUndoAction(updateCellValue,modified->number);
                }
                current->pencilMark[modified->number-1] = 0;
                removePencilMark(current,modified->number);
            }
        }
    }
    if (!data->undoMode) { //retour en mode normal dans la list undo
        addUndoAction(changeMode,0);
    }
}

void removeRules() { //Fonctionnement similaire à addRules
    //Fonction permmettant de retirer les restrictions imposées par la cellules sélectionnée

    cell* current;
    cell* modified = data->lastClicked;
    int i;

    for (i = 0; i<=8; i = i+1) {
        current = data->cells[i][modified->column];
        if (current!=modified) {
            current->rules[modified->number-1] = removeRule(current->rules[modified->number-1], modified);
        }
    }

    for (i = 0; i<=8; i = i+1) {
        current = data->cells[modified->line][i];
        if (current!=modified) {
            current->rules[modified->number-1] = removeRule(current->rules[modified->number-1], modified);
        }
    }

    int j;
    for (i = (modified->line%3==0); i<=2; i = i+1+(modified->line%3-1==i)) {
        for (j = (modified->column%3==0); j<=2; j=j+1+(modified->column%3-1==j)) {
            current = data->cells[i+modified->line-modified->line%3][j+modified->column-modified->column%3];
            current->rules[modified->number-1] = removeRule(current->rules[modified->number], modified);
        }
    }
}

void showRules(cellList* currentElement) {
    //Fonction premettant d'afficher les cellules empêchant la saisie d'un nombre donnée

    while (currentElement!=NULL) { //Boucle parcourant la liste des cellules empêchant la saisie du nombre
        printRed(currentElement->bloqueur); //Affichage d'un fond rouge pour ces cellules
        currentElement = currentElement->next; //Incrémentation
    }
}

void hideRules(cellList* currentElement) {
    //Fonction permettant de retirer les fonds rouge

    while (currentElement!=NULL) { //Boucle parcourant la liste des fonds rouge
        drawNumberBackground(currentElement->bloqueur); //Affichage d'un fond blanc
        drawNumberAtPosition(currentElement->bloqueur); //Affichage du nombre
        currentElement = currentElement->next; //Incrémentation
    }
    data->redHover = 0; //Indication qu'aucune cellule n'a de fond rouge
}