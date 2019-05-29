//
// Created by TheRolf on 03/05/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "sdl_sudoku.h"

extern sudokuGrid *data;
extern SDL_Color SDL_white;
extern SDL_Color SDL_blue;
extern SDL_Color SDL_black;
extern SDL_Color SDL_grey;

void printRect(cell* selectedCell, SDL_Color *color) {
    //Fonction affichant un cadre à l'intérieur de la cellule indiquée

    //Calcul de la postion du cadre
    SDL_Rect rect;
    rect.y = GRID_MARGIN + selectedCell->column/3*GRID_THICK_BORDER + selectedCell->column * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->column - selectedCell->column/3);
    rect.x = GRID_MARGIN + selectedCell->line/3*GRID_THICK_BORDER + selectedCell->line * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->line - selectedCell->line/3);
    //Calcul de la taille du cadre
    rect.w = GRID_CELL_SIZE;
    rect.h = GRID_CELL_SIZE;

    SDL_SetRenderDrawColorStruct(data->renderer, color); //Définition de la couleur du cadre
    int i;
    for(i = 0; i < GRID_HOVER_BORDER; i++) { //Affichage du cadre
        SDL_RenderDrawRect(data->renderer, &rect);
        rect.x++;
        rect.y++;
        rect.w -= 2;
        rect.h -= 2;
    }
}

void printHover(cell* selectedCell){
    //Fonction permettant de mettre une cellule en surbrillance

    printRect(selectedCell, &SDL_blue);
}

void removeHover(cell* selectedCell){
    //Fonction permettant qu'une celllule ne soit plus en surbrillance

    printRect(selectedCell, &SDL_white);
}

void updateHover(cell* position){
    //Fonction permettant de mettre à jour la cellule en surbrillance

    if (data->lastHovered==NULL){ //Si la souris était précédemment hors de la grille
        if (position!=NULL){ //Si la cellule est actuellement dans la grille
            printHover(position); //Mets en surbrillance la cellule survolée (en terme graphique)
            position->isHovered = 1; //Mets en surbrillance la cellule survolée (en terme de donnée)
            data->lastHovered=position;
        }
    }
    else{ //Si la souris était précédemment dans la grille
        if (!data->lastHovered->isClicked){ //Si la cellule en surbrillance n'est pas sélectionnée
            if (position!=data->lastHovered){ //Si la souris ne survole pas la case en surbrillance
                if (position==NULL){ //Si la souris est hors de la grille
                    removeHover(data->lastHovered); //La cellule dernièrement en surbrillance ne l'est plus
                    data->lastHovered->isHovered=0;
                    data->lastHovered=position;
                }
                else{ //Si la souris est dans la grille
                    removeHover(data->lastHovered); //la cellule dernièrement en surbrillance ne l'est plus
                    data->lastHovered->isHovered=0;
                    printHover(position); //La cellule survolée passe en surbrillance
                    position->isHovered=1;
                    data->lastHovered=position;
                }
            }
        }
    }

}

void drawNumberAtPosition(cell *number) {
    //Fonction permettant d'afficher un nombre dans une cellule

    // si il y a un nombre à rendre (case non vide)
    if(number->number != EMPTY_VALUE) {
        SDL_Rect rect;

        // on crée une surface nulle et on essaue de dessiner dessus
        SDL_Surface *surfaceText = NULL;

        //on convertit le nombre en string
        char *string = convertInt(number->number);

        // on essaye d'initialiser le font
        tryInitGridFont();
        // on dessine sur la surface le nombre
        surfaceText = TTF_RenderText_Solid(data->font, string, (number->isReadOnly) ? SDL_grey : SDL_black); // en gris si il ne peut pas être réécris, en noir sinon

        // s'il arrive à rendre le texte
        if(surfaceText != NULL) {
            // on crée la texture avec la surface
            SDL_Texture *texture = SDL_CreateTextureFromSurface(data->renderer, surfaceText);

            // on definit l'espace disponible pour le texte
            rect.y = GRID_MARGIN + number->column/3*GRID_THICK_BORDER + number->column * GRID_CELL_SIZE + GRID_THIN_BORDER * (number->column - number->column/3);  //controls the rect's x coordinate
            rect.x = GRID_MARGIN + number->line/3*GRID_THICK_BORDER + number->line * GRID_CELL_SIZE + GRID_THIN_BORDER * (number->line - number->line/3); // controls the rect's y coordinate
            rect.w = GRID_FONT_SIZE; // controls the width of the rect
            rect.h = GRID_FONT_SIZE; // controls the height of the rect

            // on crée un nouveau rect permettant de case rle nombre dedans l'espace disponible
            SDL_Rect *fitRect = SDL_RectFit(&rect, surfaceText);
            // on copie le rnedu dans le renderer dans l'espace donné
            SDL_RenderCopy(data->renderer, texture, NULL, fitRect);
            // on détruit la texture
            SDL_DestroyTexture(texture);
            // on libère le rect
            free(fitRect);
        }

        // on libère la surface
        SDL_FreeSurface(surfaceText);

        free(string);
    }
}

// fonction permettant de dessiner le fond des nombres disponibles
void drawNumberButtonsBackground(SDL_Color *color) {
    SDL_Rect rect = {GRID_MARGIN, GRID_SIZE + 2*GRID_MARGIN, GRID_SIZE, GRID_CELL_SIZE};
    SDL_SetRenderDrawColorStruct(data->renderer, color);
    SDL_RenderFillRect(data->renderer, &rect);
}

// fonction renvoyant si la cellule donnée possède une pencil mark
int hasPencilMark(cell *selectedCell) {
    // trouves-en une et sort
    int i = 0;
    for(i = 0; i < 9; i++) {
        if(selectedCell->rules[i] != NULL) {
            return 1;
        }
    }

    // sinon retourne 0
    return 0;
}

// fincrion permettant de dessiner les nombres disponibles à l'écriture
void drawAvailableNumbers() {
    // le rect pour se positionner
    SDL_Rect rect;
    rect.y = GRID_MARGIN*2 + GRID_SIZE;
    rect.x = GRID_MARGIN;
    rect.w = GRID_CELL_SIZE;
    rect.h = GRID_CELL_SIZE;

    // on décale un tout petit peu pour centrer tous les nombres (pas de bordures)
    rect.x += (GRID_SIZE - 9*GRID_CELL_SIZE)/2;

    // on lance le font
    tryInitGridFont();

    SDL_Surface *surface;
    SDL_Texture *texture;

    //on affiche tous les nombres disponibles
    int i;
    for(i = 0; i < 9; i++) {
        // on dessine le texte dans la surface
        char *number = convertInt(i+1);
        surface = TTF_RenderText_Solid(data->font, number, (data->lastClicked->rules[i]==NULL) ? SDL_black : SDL_white);
        // on crée la texture associée
        texture = SDL_CreateTextureFromSurface(data->renderer, surface);

        // on copie dans le renderer le texte
        SDL_Rect *fit = SDL_RectFit(&rect, surface);
        SDL_RenderCopy(data->renderer, texture, NULL, fit);

        // on libère la surface, le texture et le rect
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        free(fit);

        // on décale la position horizontale
        rect.x += GRID_CELL_SIZE;
    }
}

void drawNumberBackground(cell* selectedCell) {
    // x et y égalent à la marge + le nombre de cellules précédant cette cellule + les bordures
    SDL_Rect rect;
    rect.y = GRID_HOVER_BORDER + GRID_MARGIN + selectedCell->column/3*GRID_THICK_BORDER + selectedCell->column * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->column - selectedCell->column/3);
    rect.x = GRID_HOVER_BORDER + GRID_MARGIN + selectedCell->line/3*GRID_THICK_BORDER + selectedCell->line * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->line - selectedCell->line/3);
    // la largeur et hauteur c'est la taille de la cellule
    rect.w = GRID_CELL_SIZE - 2*GRID_HOVER_BORDER;
    rect.h = GRID_CELL_SIZE - 2*GRID_HOVER_BORDER;
    SDL_SetRenderDrawColorStruct(data->renderer, &SDL_white);
    SDL_RenderFillRect(data->renderer, &rect);
}

// retourne la cellule associée à la position dans la fenêtre
void getMousePosition(cell **c,char click){
    int x, y;
    SDL_GetMouseState(&x, &y);

    if(x > GRID_MARGIN && x < GRID_MARGIN + GRID_SIZE && y > GRID_MARGIN && y < GRID_MARGIN + GRID_SIZE){
        int xcells = (x-(x>=381) - GRID_MARGIN)/(GRID_CELL_SIZE+1);
        int ycells = (y-(y>=381) - GRID_MARGIN)/(GRID_CELL_SIZE+1);
        *c = data->cells[xcells][ycells];
    }

    if(click && x > GRID_MARGIN + 5 && x < GRID_MARGIN + GRID_SIZE - 5 && y > GRID_MARGIN*2 + GRID_SIZE && y < GRID_MARGIN*2 + GRID_SIZE + GRID_CELL_SIZE) {
        int l =  (x-GRID_MARGIN - 5)/GRID_CELL_SIZE + 1;
        *c = data->lastClicked;
        data->typedNumber = l;
    }
}
