#include <stdio.h>
#include <SDL2/SDL.h>
#include "sdl_custom_lib.h"
#include "sudoku_lib/sdl_sudoku.h"
#ifndef CONST_MAIN
#define CONST_MAIN
#endif

sudokuGrid *data;
SDL_Color SDL_white = {255, 255, 255};
SDL_Color SDL_black = {0, 0, 0};
SDL_Color SDL_blue = {0x4D, 0xD0, 0xE1};
SDL_Color SDL_lightgrey = {130,130,130};
SDL_Color SDL_grey = {0x37, 0x47, 0x4F}; // #37474F
SDL_Color SDL_lightred = {0xEF, 0x53, 0x50}; // 0xEF5350
int main(int argc, char **argv)
{
    do { //Faire les actions suivantes tant qu'aucun changement de difficulté et demandé
        sudokuGrid g;
        data = &g;

        //Initialisation des données
        if (!initializeSudoku())
            return -1;

        //Chargement d'une grille aléatoire
        if (loadGrid("../grids/", 2))
            return -1;

        initRules(); //Initialisation des restrictions

        drawSudokuGrid(); //Dessin de la grille

        //Dessin des chiffres
        int a, b;
        for (a = 0; a < 9; a++) {
            for (b = 0; b < 9; b++) {
                cell *c = data->cells[a][b];
                drawNumberAtPosition(c);
            }
        }

        SDL_RenderPresent(data->renderer); //Afficahge

        gameController(); //Lancement du jeu

        SDL_DestroyRenderer(data->renderer); //Destruction de l'affichage

        destroyAndQuit(&data->window); //Fermeture de la fenêtre
    } while (data->difficultyChanged);

    freeMemory(); //Libération de la mémoire

    return 0;
}