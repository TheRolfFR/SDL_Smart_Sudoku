//
// Created by asus on 25/05/2019.
//

#include "sdl_sudoku.h"

extern sudokuGrid *data;

void undo(){
    if(data->save != NULL){
        data->undoMode = 1;
        data->pencilMarkMode = 0;
        cell* temp = data->lastClicked;
        if (data->redHover != 0){
            hideRules(data->lastClicked->rules[data->redHover-1]);
        }
        while(data->save->actionList != NULL){
            data->typedNumber = data->save->actionList->actionData.value;
            data->save->actionList->actionData.pFunction();
            actionDone();
        }
        stepDone();
        data->lastClicked = temp;
        data->typedNumber = 0;
        data->undoMode = 0;
    }
}

void addUndoStep(void(*pFunction)(void),int value) {
    undoList *newHead = malloc(sizeof(undoList));
    newHead->actionList = NULL;

    if (data->save != NULL) {
        newHead->next = data->save;
    } else {
        newHead->next = NULL;
    }

    data->save = newHead;
    addUndoAction(pFunction, value);
}

void addUndoAction(void(*pFunction)(void),int value){
    actionList* newTail = malloc(sizeof(actionList));
    newTail->actionData.pFunction = pFunction;
    newTail->actionData.value = value;
    newTail->next = NULL;

    if(data->save->actionList == NULL){
        data->save->actionList = newTail;
    }
    else{
        actionList* temp = data->save->actionList;
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newTail;
    }
}

void actionDone(){
    actionList* temp = data->save->actionList->next;
    free(data->save->actionList);
    data->save->actionList = temp;
}

void stepDone(){
    undoList* temp = data->save->next;
    free(data->save);
    data->save = temp;
}



