//
// Created by TheRolf on 10/05/2019.
//

#include "sdl_sudoku.h"

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
