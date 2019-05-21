//
// Created by TheRolf on 10/05/2019.
//

#include "sdl_sudoku.h"
#include <string.h>

void drawPencilMark(sudokuGrid* grid, cell* selectedCell, int value) {
    // on détemrine la position de la pencil mark
    SDL_Rect rect;
    rect.y = GRID_MARGIN + selectedCell->column/3*GRID_THICK_BORDER + selectedCell->column * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->column - selectedCell->column/3);
    rect.x = GRID_MARGIN + selectedCell->line/3*GRID_THICK_BORDER + selectedCell->line * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->line - selectedCell->line/3);
    rect.w = GRID_CELL_SIZE/3;
    rect.h = GRID_CELL_SIZE/3;

    // on rend le texte en noir
    SDL_Color black = {0xCC, 0xCC, 0xCC};
    SDL_Surface *mark = TTF_RenderText_Solid(grid->font, convertInt(value), black);
    SDL_Rect *fit = SDL_RectFit(&rect, mark); // on crée un nouveau rect qui rentre dans le rect disponible

    // on ajuste la position en fonction de la position
    /*
     * 1 2 3
     * 4 5 6
     * 7 8 9
     */
    fit->x += GRID_CELL_SIZE / 3 * ((value-1)%3);
    fit->y += GRID_CELL_SIZE / 3 * ((value-1)/3);

    SDL_Texture *markTexture = SDL_CreateTextureFromSurface(grid->renderer, mark); // on crée la texture
    SDL_FreeSurface(mark); // on libère la surface
    SDL_RenderCopy(grid->renderer, markTexture, NULL, fit); // on rend la texture
    SDL_DestroyTexture(markTexture); // on libère la texture
}

void removePencilMark(sudokuGrid* grid, cell* selectedCell, int value) {
    // meme fonction que la precedente sauf que c'est en blanc
    //
    SDL_Rect rect;
    rect.y = GRID_MARGIN + selectedCell->column/3*GRID_THICK_BORDER + selectedCell->column * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->column - selectedCell->column/3);
    rect.x = GRID_MARGIN + selectedCell->line/3*GRID_THICK_BORDER + selectedCell->line * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->line - selectedCell->line/3);
    rect.w = GRID_CELL_SIZE/3;
    rect.h = GRID_CELL_SIZE/3;

    SDL_Color white = {0xFF, 0xFF, 0xFF};
    SDL_Surface *mark = TTF_RenderText_Solid(grid->font, convertInt(value), white);
    SDL_Rect *fit = SDL_RectFit(&rect, mark);

    fit->x += GRID_CELL_SIZE / 3 * ((value-1)%3);
    fit->y += GRID_CELL_SIZE / 3 * ((value-1)/3);

    SDL_Texture *markTexture = SDL_CreateTextureFromSurface(grid->renderer, mark); // on crée la texture
    SDL_FreeSurface(mark); // on libère la texture
    SDL_RenderCopy(grid->renderer, markTexture, NULL, fit); // on rend la texture
    SDL_DestroyTexture(markTexture); //
}

// fonction permettant de changer le titre de la fenêtre selon sir on est en pencil mark ou pas
void ChangeTitleMode(sudokuGrid* grid) {
    char title[TAILLE_MAX];
    strcpy(title, grid->initialTitle); // copier-coller le texte
    strcat(title, (grid->pencilMarkMode) ? " (Pencil Mark)" : ""); // rajoute (Pencil Mark) si on est en mode pencil mark
    SDL_SetWindowTitle(grid->window, title); // met à jour le titre
}