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
extern SDL_Color SDL_lightgrey;
extern SDL_Color SDL_white;
extern SDL_Color SDL_grey;
void tryInitGridFont() {
    //Fonction permetant d'initialiser la police

    if(data->font == NULL) { //Si il n'y a pas de police
        TTF_Font *Sans = TTF_OpenFont("../Sans.ttf", GRID_FONT_SIZE); //Initialisation de la police
        data->font = Sans;
    }
}

int loadGrid(char *path, int numberOfFiles) {
    //Fonction permettant de charger la grille

    srand(time(0));
    int index = rand()%numberOfFiles; //Génération d'un nombre pseudo-aléatoire entre et le nombre de fichier-1

    FILE *diffFile = NULL;
    diffFile = fopen("difficulte.txt", "r"); //Recherche de la difficulté

    char diff[TAILLE_MAX];

    memset(diff, 0, TAILLE_MAX); //Création d'une chaine de caractère vide
    if(diffFile != NULL) {
        fgets(diff, TAILLE_MAX, diffFile); //Récupération du contenu du fichier difficulté
    }

    if(diffFile == NULL || strcmp(diff, "easy") < 0 || strcmp(diff, "normal") < 0 || strcmp(diff, "hard") < 0) { //Si le fichier ne contient pas une difficulté connue
        strcpy(diff, "easy"); //Mets la difficulté sur facile
    }

    //Création du chemin vers le fichier contenant la grille
    char totalpath[TAILLE_MAX];
    strcpy(totalpath, path);
    strcat(totalpath, diff);
    strcat(totalpath, "/");
    strcat(totalpath, "grid");
    char *number = convertInt(index);
    strcat(totalpath, number);
    free(number);
    strcat(totalpath, ".txt");

    FILE *file = NULL;
    file = fopen(totalpath, "r"); //Ouverture du fichier

    cell *myCell;
    if(file != NULL) { //Si le fichier à été ouvert
        char line[TAILLE_MAX] = "";
        int l = 0, c;
        while(fgets(line, TAILLE_MAX, file)) { //Tant qu'il y a des ligne dans le fichier
            c = 0;

            while(line[c*2] != 0 && c < 9) {
                data->cells[l][c] = initCell(l, c, (line[c*2] != ' ') ? line[c*2] - '0' : -1, 0, 0);
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

    // on rend le fond en gris clair
    SDL_SetRenderDrawColorStruct(data->renderer, &SDL_lightgrey);
    SDL_RenderFillRect(data->renderer, NULL);

    // on rend le fond de la grille en blanc
    SDL_SetRenderDrawColorStruct(data->renderer, &SDL_white);
    SDL_Rect rect = {GRID_MARGIN, GRID_MARGIN, GRID_SIZE, GRID_SIZE};
    SDL_RenderFillRect(data->renderer, &rect);

    // on dessine les bordures fines de la grille
    SDL_SetRenderDrawColorStruct(data->renderer, &SDL_grey);
    int i, offset;
    for(i = 0; i < 6; i++) {
        offset = (i+ 1 + i / 2)*GRID_CELL_SIZE + i*GRID_THIN_BORDER + i/2*GRID_THICK_BORDER + GRID_MARGIN;

        //verticales
        SDL_RenderDrawLine(data->renderer, offset, GRID_MARGIN, offset, GRID_MARGIN + GRID_SIZE);

        // horizontales
        SDL_RenderDrawLine(data->renderer, GRID_MARGIN, offset, GRID_MARGIN + GRID_SIZE, offset);
    }

    // on dessine les bordures épaisses des groupes
    SDL_SetRenderDrawColorStruct(data->renderer, &SDL_grey);
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