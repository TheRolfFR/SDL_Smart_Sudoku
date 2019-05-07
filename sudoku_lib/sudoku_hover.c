//
// Created by TheRolf on 03/05/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "sdl_sudoku.h"


void printHover(cell* selectedCell){
    //affiche une bordure bleu sur la case passée en paramètre
}

void removeHover(cell* selectedCell){
    //affiche une bordure blanche sur la case passée en paramètre
}

void updateHover(cell* newHovered, sudokuGrid* data){
    printHover(newHovered);
    removeHover(data->lastHovered);
}

void updateNumber(cell* currentCell, sudokuGrid* data){
    //change la valeur du nombre dans cette case
}

void updateNumberAtPosition(sudokuGrid *grid, cell *newNumber, char isHovered, char isClicked) {
    if(grid->lastNumberUpdated == NULL || grid->lastNumberUpdated != newNumber || grid->lastNumberUpdated->isHovered != isHovered || grid->lastNumberUpdated->isClicked != isClicked) {
        // if new position update the last one
        if(grid->lastNumberUpdated != newNumber && grid->lastNumberUpdated != NULL) {
            drawNumberAtPosition(grid, grid->lastNumberUpdated, &grid->white);
        }

        // update the new one
        SDL_Color *color = NULL;
        newNumber->isHovered = isHovered;
        newNumber->isClicked = isClicked;

        printf("rendering as ");
        if(newNumber->isHovered) {
            color = &grid->hoverBackgroundColor;
            printf("hover");
        } else if(newNumber->isClicked) {
            color = &grid->clickBackgroundColor;
            printf("click");
        } else {
            color = &grid->white;
            printf("normal");
        }

        printf(" at position %d %d\n", newNumber->line, newNumber->column);
        drawNumberAtPosition(grid, newNumber, color);

        // update the new one
        grid->lastNumberUpdated = newNumber;
    }
}

void drawNumberAtPosition(sudokuGrid *grid, cell *number, SDL_Color *colorPointer) {
    SDL_Rect rect;

    // background rect
    rect.x = GRID_MARGIN + number->column/3*GRID_THICK_BORDER + number->column * GRID_CELL_SIZE + GRID_THIN_BORDER * (number->column - number->column/3);  //controls the rect's x coordinate
    rect.y = GRID_MARGIN + number->line/3*GRID_THICK_BORDER + number->line * GRID_CELL_SIZE + GRID_THIN_BORDER * (number->line - number->line/3); // controls the rect's y coordinte
    rect.w = GRID_CELL_SIZE;
    rect.h = GRID_CELL_SIZE;

    // set the background color to white
    SDL_SetRenderDrawColorStruct(grid->renderer, &grid->white);
    // fill the background with white
    SDL_RenderFillRect(grid->renderer, &rect);

    // set the color to draw with
    SDL_SetRenderDrawColorStruct(grid->renderer, colorPointer);
    // draw a rect of the color
    int i;
    SDL_Rect newRect;
    for(i = 0; i < GRID_HOVER_BORDER; i++) {
        newRect.x = rect.x + i;
        newRect.y = rect.y + i;
        newRect.w = rect.w - 2*i;
        newRect.h = rect.h - 2*i;
        SDL_RenderDrawRect(grid->renderer, &newRect);
    }

    tryInitGridFont(grid);

    // if there is a number to render
    if(number->number != -1) {
        // if the font is not defined, define it
        // create a null pointer and try to draw some text
        SDL_Surface *surfaceText = NULL;

        //convert integer to string
        char *string = convertInt(number->number);

        surfaceText = TTF_RenderText_Solid(grid->font, string, grid->black);

        // if the text rendered by the surface is not null
        if(surfaceText != NULL) {
            // create a texture
            SDL_Texture *texture = SDL_CreateTextureFromSurface(grid->renderer, surfaceText);
            // free the surface not null
            SDL_FreeSurface(surfaceText);

            // define the number rect
            rect.x = GRID_MARGIN + number->column/3*GRID_THICK_BORDER + number->column * GRID_CELL_SIZE + GRID_THIN_BORDER * (number->column - number->column/3);  //controls the rect's x coordinate
            rect.y = GRID_MARGIN + number->line/3*GRID_THICK_BORDER + number->line * GRID_CELL_SIZE + GRID_THIN_BORDER * (number->line - number->line/3); // controls the rect's y coordinate
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

void drawNumbersBackground(sudokuGrid *grid) {
    SDL_Rect rect = {GRID_MARGIN, GRID_SIZE + 2*GRID_MARGIN, GRID_SIZE, GRID_CELL_SIZE};
    SDL_SetRenderDrawColorStruct(grid->renderer, &grid->thinBorderColor);
    SDL_RenderFillRect(grid->renderer, &rect);
}

void drawHoverBackground(sudokuGrid *grid) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    if(x > GRID_MARGIN && x < GRID_MARGIN + GRID_SIZE && y > GRID_MARGIN && y < GRID_MARGIN + GRID_SIZE) {
        SDL_Rect rect;

        int xcells = (x - GRID_MARGIN)/GRID_CELL_SIZE, ycells = (y - GRID_MARGIN)/GRID_CELL_SIZE;

        do {
            rect.x = GRID_MARGIN + ((xcells < 3) ? xcells*(GRID_CELL_SIZE + GRID_THIN_BORDER) : xcells * GRID_CELL_SIZE + (xcells - xcells/3) * GRID_THIN_BORDER + xcells/3 * GRID_THICK_BORDER);
            xcells--;
        } while(rect.x > x);

        do {
            rect.y = GRID_MARGIN + ((ycells < 3) ? ycells*(GRID_CELL_SIZE + GRID_THIN_BORDER) : ycells * GRID_CELL_SIZE + (ycells - ycells/3) * GRID_THIN_BORDER + ycells/3 * GRID_THICK_BORDER);
            ycells--;
        } while(rect.y > y);

        rect.w = GRID_CELL_SIZE;
        rect.h = GRID_CELL_SIZE;

        // #4DD0E1
        SDL_Color lightblue = {0x4D, 0xD0, 0xE1};
        SDL_SetRenderDrawColorStruct(grid->renderer, &lightblue);
        for(int i = 0; i < 2; i++) {
            SDL_RenderDrawRect(grid->renderer, &rect);
            rect.x++;
            rect.y++;
            rect.w -= 2;
            rect.h -= 2;
        }
    }
}

void calculatePositionAndUpdate(sudokuGrid *grid, cell* numbers[][9]) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    if(x > GRID_MARGIN && x < GRID_MARGIN + GRID_SIZE && y > GRID_MARGIN && y < GRID_MARGIN + GRID_SIZE) {
        SDL_Rect rect;

        int xcells = (x-(x>=381) - GRID_MARGIN)/(GRID_CELL_SIZE+1), ycells = (y-(x>=381) - GRID_MARGIN)/(GRID_CELL_SIZE+1);

        while(rect.x > x && xcells > 1) {
            rect.x = GRID_MARGIN + ((xcells < 3) ? xcells*(GRID_CELL_SIZE + GRID_THIN_BORDER) : xcells * GRID_CELL_SIZE + (xcells - xcells/3) * GRID_THIN_BORDER + xcells/3 * GRID_THICK_BORDER);
            xcells--;
        }

        while(rect.y > y && ycells > 1) {
            rect.y = GRID_MARGIN + ((ycells < 3) ? ycells*(GRID_CELL_SIZE + GRID_THIN_BORDER) : ycells * GRID_CELL_SIZE + (ycells - ycells/3) * GRID_THIN_BORDER + ycells/3 * GRID_THICK_BORDER);
            ycells--;
        }

        updateNumberAtPosition(grid, numbers[ycells][xcells], 1, 0);
    }
}
