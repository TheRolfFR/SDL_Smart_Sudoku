//
// Created by asus on 09/05/2019.
//

#include "sdl_sudoku.h"


extern sudokuGrid *data;
extern SDL_Color SDL_lightgrey;
void selectCell(cell* position) {
    //Fonction permettatn de sélectionner un cellule

    if (position==NULL) { //Si la souris est hors de la grille
        if (data->lastHovered!=NULL) { //Si la souris était précédemment dans la grille
            if (data->redHover!=0) { //Si des cellules sont sur fond rouge
                hideRules(data->lastClicked->rules[data->redHover-1]); //Retrait des fonds rouge
            }
            data->lastHovered->isClicked = 0; //Désélection de la cellule sélectionnée
            data->lastClicked = NULL;
            updateHover(position); //Mise à jour de la cellule en surbrillance
            drawNumberButtonsBackground(&SDL_lightgrey); //Retrait des nombres indiquant les restrictions de la case sélectionnée
        }
    }
    else{ //Si la souris est dans la grille
        if (position!=data->lastHovered) { //Si la cellule survolée est différente de la cellule en surbrillance (c'est dire qu'une case est sélectionnée et que la souris survole une case différent de celle sélectionnée)
            if (data->redHover!=0) { //Si des cellules sont sur fond rouge
                hideRules(data->lastClicked->rules[data->redHover-1]); //Retrait des fonds rouge
            }
            data->lastHovered->isClicked = 0; //Déselection de la cellule sélectionnée
            updateHover(position); //Mise à jour de la cellule en surbrillance
            position->isClicked = 1; //Sélection de la cellule survolée
            data->lastClicked = position;
        }
        else{ //Si la souris survole la cellule actuellement en surbrillance
            if (!position->isClicked) { //Si la cellule survolée n'est pas sélectionnée
                position->isClicked = 1; //Sélection de la cellule survolé
                data->lastClicked = position;
            }
        }
        drawAvailableNumbers(data); //Affichage des restrictions concernants la case sélectionnée
    }
}

void unselect() {
    //Fonction permettant de déselectionner une cellule

    if (data->redHover!=0) { //Si il y a des cellules sur fond rouge
        hideRules(data->lastClicked->rules[data->redHover-1]); //Retrait des fonds rouge
    }
    data->lastClicked->isClicked = 0; //Déselection de la dernière cellule sélectionnée
    cell *c;
    getMousePosition(&c,0); //Obtention de la position de la souris
    updateHover(c); //Mise à jour de la cellule en surbrillance

    drawNumberButtonsBackground(&SDL_lightgrey); //Retrait des nombres indiquant les restrictions de la case sélectionnée
    data->lastClicked = NULL;
}

void changeLastClicked() {
    //Fonction permettant de changer artificiellement la dernière cellule sélectionnée (utilisé pour la fonction de retour en arrière)

    int code = data->typedNumber; //Récupération des coordonnés de la cellule à sélecctionner (codé abscisse*10+ordonné afin de rentrer dans un entier)
    data->lastClicked = data->cells[(code/10)-1][(code%10)-1]; //Changement de la dernière cellule sélectionnée
}