//
// Created by TheRolf on 21/05/2019.
//

#include "sdl_sudoku.h"

void printRed(sudokuGrid *data, cell *selectedCell) {

    // x et y égalent à la marge + le nombre de cellules précédant cette cellule + les bordures
    SDL_Rect rect;
    rect.y = GRID_HOVER_BORDER + GRID_HOVER_BORDER + GRID_MARGIN + selectedCell->column/3*GRID_THICK_BORDER + selectedCell->column * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->column - selectedCell->column/3);
    rect.x = GRID_HOVER_BORDER + GRID_HOVER_BORDER + GRID_MARGIN + selectedCell->line/3*GRID_THICK_BORDER + selectedCell->line * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->line - selectedCell->line/3);
    // la largeur et hauteur c'est la taille de la cellule
    rect.w = GRID_CELL_SIZE - 2*GRID_HOVER_BORDER;
    rect.h = GRID_CELL_SIZE - 2*GRID_HOVER_BORDER;

    // dessiner un fond rouge clair
    SDL_Color lightred;
    SDL_ColorFromHex(&lightred, 0xef5350);
    SDL_SetRenderDrawColorStruct(data->renderer, &lightred);
    SDL_RenderFillRect(data->renderer, &rect);

    rect.y -= GRID_HOVER_BORDER;
    rect.x -= GRID_HOVER_BORDER;
    rect.w += 2*GRID_HOVER_BORDER;
    rect.h += 2*GRID_HOVER_BORDER;

    // dessiner un carré rouge foncé
    SDL_Color darkred;
    SDL_ColorFromHex(&darkred, 0xf44336);
    SDL_SetRenderDrawColorStruct(data->renderer, &darkred);
    SDL_RenderDrawRect(data->renderer, &rect);

    // dessiner le nombre
    drawNumberAtPosition(data, selectedCell);
}
