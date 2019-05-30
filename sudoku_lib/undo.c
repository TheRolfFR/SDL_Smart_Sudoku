//
// Created by asus on 25/05/2019.
//

#include "sdl_sudoku.h"

extern sudokuGrid *data;

void undo(){
    //Fonction permettant de revenir en arrière d'une action

    if(data->save != NULL){ //Si la liste des étapes n'est pas vide
        data->undoMode = 1; //Indication du mode retour en arrière (permet de ne pas enregistrer les actions de mode retour en arrière comme action annulable)
        data->pencilMarkMode = 0; //Force la fin du mode annotation
        cell* temp = data->lastClicked; //Sauvergarde de la cellule sélectionnée

        if (data->redHover != 0){ //Si des cellules sont sur fond rouge
            hideRules(data->lastClicked->rules[data->redHover-1]); //Retrait des fonds rouge
        }
        while(data->save->actionList != NULL){ //Tant qu'il y a des actions à effectuer
            data->typedNumber = data->save->actionList->actionData.value; //Indique le nombre nécessaire pour effectuer l'action
            data->save->actionList->actionData.pFunction(); //Effectue l'action de retour en arrière
            actionDone(); //Efface l'action de la liste
        }
        stepDone(); //Efface l'étape de la liste
        data->lastClicked = temp; //Sélection de la case précédemment sélectionnée
        data->typedNumber = 0; //Réinitialise le nombre saisie
        data->undoMode = 0; //Fin du mode retour en arrière
    }
}

void addUndoStep(void(*pFunction)(void),int value) {
    //Fonction permettant d'ajouter une étape de la liste des étapes (en tête de liste)

    undoList *newHead = malloc(sizeof(undoList)); //Allocation de la mémoire
    newHead->actionList = NULL; //Initialisation

    if (data->save != NULL) { //Si la liste n'est pas vide
        newHead->next = data->save; //Ajout de la liste derrière le nouvel élément
    } else { //Si la liste est vide
        newHead->next = NULL; //Indication que cet élémenet est le dernier
    }

    data->save = newHead; //Mise à jour de la liste des étapes
    addUndoAction(pFunction, value); //Ajout de l'action passé en paramètre à la liste
}

void addUndoAction(void(*pFunction)(void),int value){
    //Fonction permettant d'ajouter une action à la fin de la liste des actions de l'étape en cours

    actionList* newTail = malloc(sizeof(actionList)); //Allocation de la mémoire

    //Initialisation
    newTail->actionData.pFunction = pFunction;
    newTail->actionData.value = value;
    newTail->next = NULL;

    if(data->save->actionList == NULL){ //Si la liste est vide
        data->save->actionList = newTail; //Ajout de l'élément
    }
    else{ //Si la liste n'est pas vide
        actionList* temp = data->save->actionList;
        while (temp->next != NULL){ //Boucle de recherche de la queue
            temp = temp->next;
        }
        temp->next = newTail; //Ajout de l'action en queue de liste
    }
}

void actionDone(){
    //Fonction permettant de retirer une action effectuée de la liste

    actionList* temp = data->save->actionList->next; //Sauvegarde de la suite de la liste
    free(data->save->actionList); //Suppression de l'élément en tête
    data->save->actionList = temp; //Mise à jour de la liste
}

void stepDone(){
    //Fonction permettant de retirer une étape de la liste

    undoList* temp = data->save->next; //Sauvegarde de la suite de la liste
    free(data->save); //Suppression de l'élément en tête
    data->save = temp; //Mise à jour de la liste
}



