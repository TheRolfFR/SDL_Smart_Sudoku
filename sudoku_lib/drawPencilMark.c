//
// Created by TheRolf on 10/05/2019.
//

#include "sdl_sudoku.h"
#include <string.h>

extern sudokuGrid *data;
extern SDL_Color SDL_lightgrey;
void drawPencilMark(cell* selectedCell, int value) {
    //Fonction affichant une annotation

    //Détermination de la dimension d'une annotation
    SDL_Rect rect;
    rect.y = GRID_MARGIN + selectedCell->column/3*GRID_THICK_BORDER + selectedCell->column * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->column - selectedCell->column/3);
    rect.x = GRID_MARGIN + selectedCell->line/3*GRID_THICK_BORDER + selectedCell->line * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->line - selectedCell->line/3);
    rect.w = GRID_CELL_SIZE/3;
    rect.h = GRID_CELL_SIZE/3;

    char *number = convertInt(value); //Converstion de "value" en chaine de caractère (prérequis à TTF_RenderText_Solid()
    SDL_Surface *mark = TTF_RenderText_Solid(data->font, number, SDL_lightgrey); //Dessin de l'annotation
    free(number); //Libération de la chaine de caractère
    SDL_Rect *fit = SDL_RectFit(&rect, mark); //Mise à l'échelle du dessin

    //Ajustement de la position de l'annotation au sein de la case
    fit->x += GRID_CELL_SIZE / 3 * ((value-1)%3);
    fit->y += GRID_CELL_SIZE / 3 * ((value-1)/3);

    SDL_Texture *markTexture = SDL_CreateTextureFromSurface(data->renderer, mark); //Création de la texture associée (permet d'utiliser la carte graphique de l'ordinateur)
    SDL_FreeSurface(mark); //Libération de de la surface
    SDL_RenderCopy(data->renderer, markTexture, NULL, fit); //Affichage de la texture
    SDL_DestroyTexture(markTexture); //Libération de la texture
    free(fit); //Libération du rectangle de mise à l'échelle
}

void removePencilMark(cell* selectedCell, int value) {
    //Fonction éffaçant une annotation (fonctionnement similaire à drawPencilMark mais affiche un carré blanc)

    SDL_Rect rect;
    rect.y = GRID_MARGIN + selectedCell->column/3*GRID_THICK_BORDER + selectedCell->column * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->column - selectedCell->column/3);
    rect.x = GRID_MARGIN + selectedCell->line/3*GRID_THICK_BORDER + selectedCell->line * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->line - selectedCell->line/3);
    rect.w = GRID_CELL_SIZE/3;
    rect.h = GRID_CELL_SIZE/3;

    SDL_Color white = {0xFF, 0xFF, 0xFF};
    char *number = convertInt(value);
    SDL_Surface *mark = TTF_RenderText_Solid(data->font, number, white);
    free(number);
    SDL_Rect *fit = SDL_RectFit(&rect, mark);

    fit->x += GRID_CELL_SIZE / 3 * ((value-1)%3);
    fit->y += GRID_CELL_SIZE / 3 * ((value-1)/3);

    SDL_Texture *markTexture = SDL_CreateTextureFromSurface(data->renderer, mark);
    SDL_FreeSurface(mark);
    SDL_RenderCopy(data->renderer, markTexture, NULL, fit);
    SDL_DestroyTexture(markTexture);
    free(fit);
}


void ChangeTitleMode() {
    //Fonction permettant d'indiquer le mode (annotation ou non) via le titre de la fenêtre

    char title[TAILLE_MAX];
    strcpy(title, data->initialTitle); //Copie du titre original
    strcat(title, (data->pencilMarkMode) ? " (Pencil Mark)" : ""); //Ajout de la mention (Pencil Mark) dépendant du mode
    SDL_SetWindowTitle(data->window, title); //Mise à jour du titre
}