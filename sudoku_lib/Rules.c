//
// Created by TheRolf on 10/05/2019.
//

#include "sdl_sudoku.h"

cellList* addRule(cellList *list, cell *cellToAdd) {
    // on créé l'élément
    cellList *newHead = malloc(sizeof(cellList));
    newHead->bloqueur = cellToAdd;

    // si la liste est pas nulle, alors on ajoute en tete
    if(list != NULL) {
        newHead->next = list;
    } else {
        newHead->next = NULL;
    }

    // enfin on retourne la nouvelle tête
    return newHead;
}

cellList *removeRule(cellList *list, cell *cellToRemove) {
    // sir ma ilste est vide je renvoie que dalle
    if(list == NULL) {
        return NULL;
    } else {
        cellList *precedent = NULL;
        cellList *actuel = list;
        while(actuel != NULL && actuel->bloqueur != cellToRemove) {
            precedent = actuel;
            actuel = actuel->next;
        }


        // s'il l'a trouvé
        if(actuel != NULL) {
            // si c'est le premier
            if(precedent == NULL) {
                cellList *newHead = actuel->next;
                free(actuel);
                return newHead;
            } else {
                // si c'est pas le dernier
                // il faut tous les lier le précédent et le suivant en suprimant l'actuel
                precedent->next = actuel->next;
                free(actuel);
                return list;
            }
        } else {
            // il l'a pas trouve
            return list;
        }
    }
}

void printRules(cell* myCell) {
    printf("1 2 3 4 5 6 7 8 9\n");
    int i;
    for(i = 0; i < 9; i++) {
        printf("%d ", myCell->rules[i]==NULL);
    }
    printf("\n");
}