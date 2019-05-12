//
// Created by TheRolf on 03/05/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>
#include "../sdl_custom_lib.h"
#include "sdl_sudoku.h"

void tryInitGridFont(sudokuGrid *grid) {
    TTF_Font *Sans = TTF_OpenFont("../Sans.ttf", GRID_FONT_SIZE);

    grid->font = Sans;
}

int loadGrid(sudokuGrid *grid, char *path, int numberOfFiles) {
    // on choisit une grille au hasard
    srand(time(0));
    int index = rand()%numberOfFiles;

    // on va jusqu'au chemin
    char totalpath[TAILLE_MAX];
    strcpy(totalpath, path);
    strcat(totalpath, "grid");
    strcat(totalpath, convertInt(index));
    strcat(totalpath, ".txt");

    // on tente d'ouvrir le fichier
    FILE *file = NULL;
    file = fopen(totalpath, "r");

    cell *myCell;
    if(file != NULL) {
        // si on a réussi à l'ouvrir
        char line[TAILLE_MAX] = "";
        int l = 0, c;
        while(fgets(line, TAILLE_MAX, file)) {
            c = 0;

            // tant que la ligne n'est pas terminée on crée les cellules
            while(line[c*2] != 0 && c < 9) {
                grid->cells[l][c] = initCell(l, c, (line[c*2] != ' ') ? line[c*2] - '0' : -1, 0, 0);
                c++;
            }

            // si il manque des cellules
            if(c < 9) {
                // on crée les restantes
                for(c = c; c < 9; c++) {
                    myCell = initCell(l, c, EMPTY_VALUE, 0, 0);

                    grid->cells[l][c] = myCell;
                }
            }

            // on reset la ligne avec des zéros
            memset(line,0,strlen(line));
            l++;
        }

        fclose(file);
        return 0;
    } else { // erreur bla bla
        fprintf(stderr, "Impossible to open %s\n", totalpath);
    }
    return -1;
}

void drawSudokuGrid(sudokuGrid *grid)  {
    // on nettoie le rendu
    SDL_RenderClear(grid->renderer);

    SDL_Color lightgrey = {189,189,189}, white = {255,255,255}, grey = {158,158,158};

    // on rend le fond en gris clair
    SDL_SetRenderDrawColorStruct(grid->renderer, &lightgrey);
    SDL_RenderFillRect(grid->renderer, NULL);

    // on rend le fond de la grille en blanc
    SDL_SetRenderDrawColorStruct(grid->renderer, &white);
    SDL_Rect rect = {GRID_MARGIN, GRID_MARGIN, GRID_SIZE, GRID_SIZE};
    SDL_RenderFillRect(grid->renderer, &rect);

    // on dessine les bordures fines de la grille
    SDL_SetRenderDrawColorStruct(grid->renderer, &grey);
    int i, offset;
    for(i = 0; i < 6; i++) {
        offset = (i+ 1 + i / 2)*GRID_CELL_SIZE + i*GRID_THIN_BORDER + i/2*GRID_THICK_BORDER + GRID_MARGIN;

        //verticales
        SDL_RenderDrawLine(grid->renderer, offset, GRID_MARGIN, offset, GRID_MARGIN + GRID_SIZE);

        // horizontales
        SDL_RenderDrawLine(grid->renderer, GRID_MARGIN, offset, GRID_MARGIN + GRID_SIZE, offset);
    }

    // on dessine les bordures épaisses des groupes
    SDL_SetRenderDrawColorStruct(grid->renderer, &grey);
    SDL_Rect vert = {0, GRID_MARGIN, GRID_THICK_BORDER, GRID_SIZE}, hori = {GRID_MARGIN, 0, GRID_SIZE, GRID_THICK_BORDER};
    for(i = 0; i < 2; i++) {
        offset = 3*(1+i)*GRID_CELL_SIZE + 2*(i+1)*GRID_THIN_BORDER + GRID_MARGIN + i * GRID_THICK_BORDER;
        vert.x = offset;
        hori.y = offset;

        // verticales
        SDL_RenderFillRect(grid->renderer, &vert);

        // horizontales
        SDL_RenderFillRect(grid->renderer, &hori);
    }
}