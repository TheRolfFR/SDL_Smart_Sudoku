//
// Created by TheRolf on 10/05/2019.
//

#include "sdl_sudoku.h"

void drawPencilMark(sudokuGrid* grid, cell* selectedCell) {
    SDL_Rect rect;
    rect.y = GRID_MARGIN + selectedCell->column/3*GRID_THICK_BORDER + selectedCell->column * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->column - selectedCell->column/3);
    rect.x = GRID_MARGIN + selectedCell->line/3*GRID_THICK_BORDER + selectedCell->line * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->line - selectedCell->line/3);
    rect.w = GRID_CELL_SIZE/3;
    rect.h = GRID_CELL_SIZE/3;

    int i;
    for(i = 0; i < 9; i++) {
        if(selectedCell->pencilMark[i] != 0) {
            SDL_Color black = {0xCC, 0xCC, 0xCC};
            SDL_Surface *mark = TTF_RenderText_Solid(grid->font, convertInt(selectedCell->pencilMark[i]), black);
            SDL_Rect *fit = SDL_RectFit(&rect, mark);

            fit->x += GRID_CELL_SIZE / 3 * (i%3);
            fit->y += GRID_CELL_SIZE / 3 * (i/3);

            SDL_Texture *markTexture = SDL_CreateTextureFromSurface(grid->renderer, mark);
            SDL_FreeSurface(mark);
            SDL_RenderCopy(grid->renderer, markTexture, NULL, fit);
        }
    }
}
