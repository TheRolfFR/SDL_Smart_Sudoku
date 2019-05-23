//
// Created by TheRolf on 03/05/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "sdl_sudoku.h"

extern sudokuGrid *data;
// dessine une bodure de la couleur choisie sur la case choisie
void printRect(cell* selectedCell, SDL_Color *color) {
    // x et y égalent à la marge + le nombre de cellules précédant cette cellule + les bordures
    SDL_Rect rect;
    rect.y = GRID_MARGIN + selectedCell->column/3*GRID_THICK_BORDER + selectedCell->column * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->column - selectedCell->column/3);
    rect.x = GRID_MARGIN + selectedCell->line/3*GRID_THICK_BORDER + selectedCell->line * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->line - selectedCell->line/3);
    // la largeur et hauteur c'est la taille de la cellule
    rect.w = GRID_CELL_SIZE;
    rect.h = GRID_CELL_SIZE;

    // on change la couleur de rendu
    SDL_SetRenderDrawColorStruct(data->renderer, color);
    int i;
    for(i = 0; i < GRID_HOVER_BORDER; i++) {
        SDL_RenderDrawRect(data->renderer, &rect);
        rect.x++;
        rect.y++;
        rect.w -= 2;
        rect.h -= 2;
    }
}

//affiche une bordure bleu sur la case passée en paramètre
void printHover(cell* selectedCell){
    SDL_Color bleu = {0x4D, 0xD0, 0xE1};
    printRect(selectedCell, &bleu);
}

//affiche une bordure blanche sur la case passée en paramètre
void removeHover(cell* selectedCell){
    SDL_Color blanc = {0xFF, 0xFF, 0xFF};
    printRect(selectedCell, &blanc);
}

void updateHover(cell* position){
    if (data->lastHovered==NULL){ //la souris était précédemment hors de la grid
        if (position!=NULL){ //la souris est entrée dans la grid
            printHover(position);
            position->isHovered = 1;
            data->lastHovered=position;
        }
    }
    else{ //la souris était précédemment dans la grid

        if (!data->lastHovered->isClicked){ //aucune case n'est séléctionnée
            if (position!=data->lastHovered){ // la souris n'a pas changée de case
                if (position==NULL){ //la souris est sortis de la grid
                    removeHover(data->lastHovered);
                    data->lastHovered->isHovered=0;
                    data->lastHovered=position;
                }
                else{ //la souris est tjr dans la grid
                    removeHover(data->lastHovered);
                    data->lastHovered->isHovered=0;
                    printHover(position);
                    position->isHovered=1;
                    data->lastHovered=position;
                }
            }
        }
    }

}

void drawNumberAtPosition(cell *number) {
    // si il y a un nombre à rendre (case non vide)
    if(number->number != EMPTY_VALUE) {
        SDL_Rect rect;

        // on crée une surface nulle et on essaue de dessiner dessus
        SDL_Surface *surfaceText = NULL;

        //on convertit le nombre en string
        char *string = convertInt(number->number);

        SDL_Color black = {0, 0, 0};
        SDL_Color grey = {0x37, 0x47, 0x4F}; // #37474F

        // on essaye d'initialiser le font
        tryInitGridFont();
        // on dessine sur la surface le nombre
        surfaceText = TTF_RenderText_Solid(data->font, string, (number->isReadOnly) ? grey : black); // en gris si il ne peut pas être réécris, en noir sinon

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

            // on libère la surface
            SDL_FreeSurface(surfaceText);
            // on copie le rnedu dans le renderer dans l'espace donné
            SDL_RenderCopy(data->renderer, texture, NULL, fitRect);
            // on détruit la texture
            SDL_DestroyTexture(texture);
        }
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

    SDL_Color black = {0,0,0};
    SDL_Color white = {255, 255, 255};

    //on affiche tous les nombres disponibles
    int i;
    for(i = 0; i < 9; i++) {
        // on dessine le texte dans la surface
        surface = TTF_RenderText_Solid(data->font, convertInt(i+1), (data->lastClicked->rules[i]==NULL) ? black : white);
        // on crée la texture associée
        texture = SDL_CreateTextureFromSurface(data->renderer, surface);

        // on copie dans le renderer le texte
        SDL_RenderCopy(data->renderer, texture, NULL, SDL_RectFit(&rect, surface));

        // on libère la surface et la texture
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

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

    SDL_Color white = {0xFF, 0xFF, 0xFF};
    SDL_SetRenderDrawColorStruct(data->renderer, &white);
    SDL_RenderFillRect(data->renderer, &rect);
}

// retourne la cellule associée à la position dans la fenêtre
cell* getMousePosition(){
    int x, y;
    cell* currentCell=NULL;
    SDL_GetMouseState(&x, &y);

    if(x > GRID_MARGIN && x < GRID_MARGIN + GRID_SIZE && y > GRID_MARGIN && y < GRID_MARGIN + GRID_SIZE){
        int xcells = (x-(x>=381) - GRID_MARGIN)/(GRID_CELL_SIZE+1);
        int ycells = (y-(y>=381) - GRID_MARGIN)/(GRID_CELL_SIZE+1);
        currentCell = data->cells[xcells][ycells];
    }
    return currentCell;
}
