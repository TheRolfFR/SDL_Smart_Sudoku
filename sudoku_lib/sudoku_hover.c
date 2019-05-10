//
// Created by TheRolf on 03/05/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "sdl_sudoku.h"

// dessine une bodure de la couleur choisie sur la case choisie
void printRect(sudokuGrid *grid, cell* selectedCell, SDL_Color *color) {
    // x et y égalent à la marge + le nombre de cellules précédant cette cellule + les bordures
    SDL_Rect rect;
    rect.y = GRID_MARGIN + selectedCell->column/3*GRID_THICK_BORDER + selectedCell->column * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->column - selectedCell->column/3);
    rect.x = GRID_MARGIN + selectedCell->line/3*GRID_THICK_BORDER + selectedCell->line * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->line - selectedCell->line/3);
    // la largeur et hauteur c'est la taille de la cellule
    rect.w = GRID_CELL_SIZE;
    rect.h = GRID_CELL_SIZE;

    // on change la couleur de rendu
    SDL_SetRenderDrawColorStruct(grid->renderer, color);
    int i;
    for(i = 0; i < GRID_HOVER_BORDER; i++) {
        SDL_RenderDrawRect(grid->renderer, &rect);
        rect.x++;
        rect.y++;
        rect.w -= 2;
        rect.h -= 2;
    }
}

//affiche une bordure bleu sur la case passée en paramètre
void printHover(sudokuGrid *grid, cell* selectedCell){
    SDL_Color bleu = {0x4D, 0xD0, 0xE1};
    printRect(grid, selectedCell, &bleu);
}

//affiche une bordure blanche sur la case passée en paramètre
void removeHover(sudokuGrid *grid, cell* selectedCell){
    SDL_Color blanc = {0xFF, 0xFF, 0xFF};
    printRect(grid, selectedCell, &blanc);
}

void updateHover(sudokuGrid *grid, cell* position){
    if (grid->lastHovered==NULL){ //la souris était précédemment hors de la grid
        if (position!=NULL){ //la souris est entrée dans la grid
            printHover(grid, position);
            position->isHovered = 1;
            grid->lastHovered=position;
        }
    }
    else{ //la souris était précédemment dans la grid

        if (!grid->lastHovered->isClicked){ //aucune case n'est séléctionnée
            if (position!=grid->lastHovered){ // la souris n'a pas changée de case
                if (position==NULL){ //la souris est sortis de la grid
                    removeHover(grid, grid->lastHovered);
                    grid->lastHovered->isHovered=0;
                    grid->lastHovered=position;
                }
                else{ //la souris est tjr dans la grid
                    removeHover(grid, grid->lastHovered);
                    grid->lastHovered->isHovered=0;
                    printHover(grid, position);
                    position->isHovered=1;
                    grid->lastHovered=position;
                }
            }
        }
    }

}

void drawNumberAtPosition(sudokuGrid *grid, cell *number) {
    // if there is a number to render
    if(number->number != EMPTY_VALUE) {
        SDL_Rect rect;
        // if the font is not defined, define it
        // create a null pointer and try to draw some text
        SDL_Surface *surfaceText = NULL;

        //convert integer to string
        char *string = convertInt(number->number);

        SDL_Color black = {0, 0, 0};
        SDL_Color grey = {0x37, 0x47, 0x4F}; //37474F

        tryInitGridFont(grid);
        surfaceText = TTF_RenderText_Solid(grid->font, string, (number->isReadOnly) ? grey : black);

        // if the text rendered by the surface is not null
        if(surfaceText != NULL) {
            // create a texture
            SDL_Texture *texture = SDL_CreateTextureFromSurface(grid->renderer, surfaceText);
            // free the surface not null
            SDL_FreeSurface(surfaceText);

            // define the number rect
            rect.y = GRID_MARGIN + number->column/3*GRID_THICK_BORDER + number->column * GRID_CELL_SIZE + GRID_THIN_BORDER * (number->column - number->column/3);  //controls the rect's x coordinate
            rect.x = GRID_MARGIN + number->line/3*GRID_THICK_BORDER + number->line * GRID_CELL_SIZE + GRID_THIN_BORDER * (number->line - number->line/3); // controls the rect's y coordinate
            rect.w = GRID_FONT_SIZE; // controls the width of the rect
            rect.h = GRID_FONT_SIZE; // controls the height of the rect

            // make it fit to the rect of my text surface
            SDL_Rect *fitRect = SDL_RectFit(&rect, surfaceText);

            // copy it on the render
            SDL_RenderCopy(grid->renderer, texture, NULL, fitRect);
            // destroy the texture created
            SDL_DestroyTexture(texture);
        }
    }
}

void drawNumberButtonsBackground(sudokuGrid *grid) {
    SDL_Rect rect = {GRID_MARGIN, GRID_SIZE + 2*GRID_MARGIN, GRID_SIZE, GRID_CELL_SIZE};
    SDL_SetRenderDrawColorStruct(grid->renderer, &grid->thinBorderColor);
    SDL_RenderFillRect(grid->renderer, &rect);
}

void drawNumberBackground(sudokuGrid *grid, cell* selectedCell) {
    // x et y égalent à la marge + le nombre de cellules précédant cette cellule + les bordures
    SDL_Rect rect;
    rect.y = GRID_HOVER_BORDER + GRID_MARGIN + selectedCell->column/3*GRID_THICK_BORDER + selectedCell->column * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->column - selectedCell->column/3);
    rect.x = GRID_HOVER_BORDER + GRID_MARGIN + selectedCell->line/3*GRID_THICK_BORDER + selectedCell->line * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->line - selectedCell->line/3);
    // la largeur et hauteur c'est la taille de la cellule
    rect.w = GRID_CELL_SIZE - 2*GRID_HOVER_BORDER;
    rect.h = GRID_CELL_SIZE - 2*GRID_HOVER_BORDER;

    SDL_Color white = {0xFF, 0xFF, 0xFF};
    SDL_SetRenderDrawColorStruct(grid->renderer, &white);
    SDL_RenderFillRect(grid->renderer, &rect);
}

cell* getMousePosition(sudokuGrid* data){
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
