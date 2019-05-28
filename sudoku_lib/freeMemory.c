//
// Created by TheRolf on 28/05/2019.
//

#include "sdl_sudoku.h"

extern sudokuGrid* data;
void freeMemory() {
    //Fonction liberant les espaces mémoires alloués dynamiquement

    free(data->window);
    free(data->windowSurface);
    free(data->renderer);
    free(data->font);

    //Libération des listes chainées des restrictions pour chaque cellule
    int a, b, c;
    cellList *rule;
    cellList *nextRule;
    for(a = 0; a < 9; a++) {
        for(b = 0; b < 9; b++) {
            for(c = 0; c < 9; c++) {
                rule = data->cells[a][b]->rules[c];
                while(rule != NULL) {
                    nextRule = rule->next;
                    free(rule);
                    rule = nextRule;
                }
            }
        }
    }

    //Libération des boutons de difficulté
    free(data->easy);
    free(data->normal);
    free(data->hard);

    //Libération de la liste de sauvegarde des actions
    while(data->save != NULL) {
        while(data->save->actionList != NULL) {
            actionDone();
        }

        stepDone();
    }
}
