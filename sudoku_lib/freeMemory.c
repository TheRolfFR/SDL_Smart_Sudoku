//
// Created by TheRolf on 28/05/2019.
//

#include "sdl_sudoku.h"

extern sudokuGrid* data;
void freeMemory() {
    // basic data
    free(data->window);
    free(data->windowSurface);
    free(data->renderer);
    free(data->font);
    free(data->lastHovered);
    free(data->lastClicked);

    // the tab cells
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

    // difficulty buttons
    free(data->easy);
    free(data->normal);
    free(data->hard);

    // undo list
    undoList *undo = data->save;
    undoList *nextUndo;

    actionList *action;
    actionList *nextAction;
    while(undo != NULL) {
        nextUndo = undo->next;

        action = undo->actionList;
        while(action != NULL) {
            nextAction = action->next;
            free(action);
            action = nextAction;
        }

        free(undo);
        undo = nextUndo;
    }
}
