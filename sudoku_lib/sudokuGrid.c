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

extern sudokuGrid *data;
void tryInitGridFont() {
    if(data->font == NULL) {
        TTF_Font *Sans = TTF_OpenFont("../Sans.ttf", GRID_FONT_SIZE);

        data->font = Sans;
    }
}

int loadGrid(char *path, int numberOfFiles) {
    // on genere un numero au hasard
    srand(time(0));
    int index = rand()%numberOfFiles;

    //on essaye d'aller cherche la difficulte
    FILE *diffFile = NULL;
    diffFile = fopen("difficulte.txt", "r");

    char diff[TAILLE_MAX];

    memset(diff, 0, TAILLE_MAX);
    if(diffFile != NULL) {
        fgets(diff, TAILLE_MAX, diffFile);
    }

    if(diffFile == NULL || strcmp(diff, "easy") < 0 || strcmp(diff, "normal") < 0 || strcmp(diff, "hard") < 0) {
        strcpy(diff, "easy");
    }

    // on va jusqu'au chemin
    char totalpath[TAILLE_MAX];
    strcpy(totalpath, path);
    strcat(totalpath, diff);
    strcat(totalpath, "/");
    strcat(totalpath, "grid");
    char *number = convertInt(index);
    strcat(totalpath, number);
    free(number);
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
                data->cells[l][c] = initCell(l, c, (line[c*2] != ' ') ? line[c*2] - '0' : -1, 0, 0);
                if(line[c*2]!=' '){
                    data->emptyCell = data->emptyCell-1;
                }
                c++;
            }

            // si il manque des cellules
            if(c < 9) {
                // on crée les restantes
                for(c = c; c < 9; c++) {
                    myCell = initCell(l, c, EMPTY_VALUE, 0, 0);

                    data->cells[l][c] = myCell;
                }
            }

            // on reset la ligne avec des zéros
            memset(line,0,strlen(line));
            l++;
        }

        fclose(file);
        return 0;
    } else { // erreur
        fprintf(stderr, "Impossible to open %s\n", totalpath);
    }
    return -1;
}

void drawSudokuGrid()  {
    // on nettoie le rendu
    SDL_RenderClear(data->renderer);

    SDL_Color lightgrey = {189,189,189}, white = {255,255,255}, grey = {158,158,158};

    // on rend le fond en gris clair
    SDL_SetRenderDrawColorStruct(data->renderer, &lightgrey);
    SDL_RenderFillRect(data->renderer, NULL);

    // on rend le fond de la grille en blanc
    SDL_SetRenderDrawColorStruct(data->renderer, &white);
    SDL_Rect rect = {GRID_MARGIN, GRID_MARGIN, GRID_SIZE, GRID_SIZE};
    SDL_RenderFillRect(data->renderer, &rect);

    // on dessine les bordures fines de la grille
    SDL_SetRenderDrawColorStruct(data->renderer, &grey);
    int i, offset;
    for(i = 0; i < 6; i++) {
        offset = (i+ 1 + i / 2)*GRID_CELL_SIZE + i*GRID_THIN_BORDER + i/2*GRID_THICK_BORDER + GRID_MARGIN;

        //verticales
        SDL_RenderDrawLine(data->renderer, offset, GRID_MARGIN, offset, GRID_MARGIN + GRID_SIZE);

        // horizontales
        SDL_RenderDrawLine(data->renderer, GRID_MARGIN, offset, GRID_MARGIN + GRID_SIZE, offset);
    }

    // on dessine les bordures épaisses des groupes
    SDL_SetRenderDrawColorStruct(data->renderer, &grey);
    SDL_Rect vert = {0, GRID_MARGIN, GRID_THICK_BORDER, GRID_SIZE}, hori = {GRID_MARGIN, 0, GRID_SIZE, GRID_THICK_BORDER};
    for(i = 0; i < 2; i++) {
        offset = 3*(1+i)*GRID_CELL_SIZE + 2*(i+1)*GRID_THIN_BORDER + GRID_MARGIN + i * GRID_THICK_BORDER;
        vert.x = offset;
        hori.y = offset;

        // verticales
        SDL_RenderFillRect(data->renderer, &vert);

        // horizontales
        SDL_RenderFillRect(data->renderer, &hori);
    }

    fillAndDrawButton(data->easy, "Facile");
    fillAndDrawButton(data->normal, "Normal");
    fillAndDrawButton(data->hard, "Difficile");
}