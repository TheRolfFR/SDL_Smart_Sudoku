//
// Created by TheRolf on 21/05/2019.
//

#include "sdl_sudoku.h"

extern sudokuGrid *data;
void printRed(cell *selectedCell) {

    // x et y égalent à la marge + le nombre de cellules précédant cette cellule + les bordures
    SDL_Rect rect;
    rect.y = GRID_HOVER_BORDER + GRID_MARGIN + selectedCell->column/3*GRID_THICK_BORDER + selectedCell->column * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->column - selectedCell->column/3);
    rect.x = GRID_HOVER_BORDER + GRID_MARGIN + selectedCell->line/3*GRID_THICK_BORDER + selectedCell->line * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->line - selectedCell->line/3);
    // la largeur et hauteur c'est la taille de la cellule
    rect.w = GRID_CELL_SIZE - 2*GRID_HOVER_BORDER;
    rect.h = GRID_CELL_SIZE - 2*GRID_HOVER_BORDER;

    // dessiner un fond rouge clair
    SDL_Color lightred = {0xEF, 0x53, 0x50}; // 0xEF5350
    SDL_SetRenderDrawColorStruct(data->renderer, &lightred);
    SDL_RenderFillRect(data->renderer, &rect);

    // dessiner le nombre
    drawNumberAtPosition(selectedCell);
}
