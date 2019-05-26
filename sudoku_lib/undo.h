//
// Created by asus on 25/05/2019.
//

#ifndef SDL_SUDOKU_UNDO_H
#define SDL_SUDOKU_UNDO_H

typedef struct action{
    void (*pFunction)(void);
    int value;
}action;

typedef struct actionList{
    action actionData;
    struct actionList* next;
}actionList;

typedef struct undoList{
    actionList* actionList;
    struct undoList* next;
}undoList;

void addUndoStep(void (*pFunction)(void),int);
void addUndoAction(void (*pFunction)(void),int);
void undo(void);
void actionDone(void);
void stepDone(void);


#endif //SDL_SUDOKU_UNDO_H
