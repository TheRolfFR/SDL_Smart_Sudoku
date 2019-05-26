//
// Created by asus on 25/05/2019.
//

#include "sdl_sudoku.h"

extern sudokuGrid *data;

void undo(){
    if(data->save != NULL){
        while(data->save->actionList->next != NULL){
            data->typedNumber = data->save->actionList->actionData.value;
            data->save->actionList->actionData.pFunction();
            //actionDone();
        }

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

    if(data->save->actionList == NULL){
        data->save->actionList = newTail;
    }
    else{
        actionList* temp = data->save->actionList;
        while (temp->next !=NULL){
            temp = temp->next;
        }
        temp->next = newTail;
    }
}



