//
// Created by asus on 23/05/2019.
//

#include "sdl_sudoku.h"

extern sudokuGrid* data;
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