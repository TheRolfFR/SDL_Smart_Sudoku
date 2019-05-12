//
// Created by TheRolf on 10/05/2019.
//

#include "sdl_sudoku.h"

// fonction ajouter tete d'une liste chainée
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

// fonction supprimer d'une liste chainée
cellList *removeRule(cellList *list, cell *cellToRemove) {
    // sir ma ilste est vide je renvoie que c'est nul
    if(list == NULL) {
        return NULL;
    } else {
        // sinon
        cellList *precedent = NULL;
        cellList *actuel = list;
        // j'avance jusqu'à la supposée case en question
        while(actuel != NULL && actuel->bloqueur != cellToRemove) {
            precedent = actuel;
            actuel = actuel->next;
        }


        // s'il l'a trouvée
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
                free(actuel); // on libère l'élément a supprimer (actuel == cellToRemove)
                return list;
            }
        } else {
            // il l'a pas trouve on retourne la liste telle qu'elle
            return list;
        }
    }
}

// fonction de debug pour voir quels chiffres on peut taper
void printRules(cell* myCell) {
    printf("1 2 3 4 5 6 7 8 9\n");
    int i;
    for(i = 0; i < 9; i++) {
        printf("%d ", myCell->rules[i]==NULL);
    }
    printf("\n");
}