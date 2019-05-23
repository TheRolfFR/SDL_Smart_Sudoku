//
// Created by TheRolf on 08/05/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sdl_sudoku.h"

/* Constantes de masque NE PAS TOUCHER */
#define RED_MASK   0xFF000000
#define GREEN_MASK 0x00FF0000
#define BLUE_MASK  0x0000FF00
#define ALPHA_MASK 0x000000FF

extern sudokuGrid *data;
int initializeSudoku() {
    int succes = 1;

    //Initialision de SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
        fprintf(stderr, "SDL n'a pas pu etre initialise ! SDL_Error: %s\n", SDL_GetError() );
        succes = 0;
    }
    else {
        //Création de la fenêtre
        data->window = NULL;
        strcpy(data->initialTitle, "Smart Sudoku");
        data->window = SDL_CreateWindow( data->initialTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GRID_SIZE + 2*GRID_MARGIN, GRID_SIZE + 3*GRID_MARGIN + GRID_BOTTOMSPACE, SDL_WINDOW_SHOWN );
        if( data->window == NULL ) {
            fprintf(stderr, "La fenetre n'a pas pu etre cree ! SDL_Error: %s\n", SDL_GetError());
            succes = 0;
        }
        else {
            //Récupération de la surface de la fenêtre
            data->windowSurface = SDL_GetWindowSurface( data->window );

            //Initialisation de la police d'écriture
            tryInitGridFont();
            data->font = NULL;
            data->font = TTF_OpenFont("../Sans.ttf", 60);


            //Changement de l'icône
            SDL_Surface *bg = SDL_CreateRGBSurface( SDL_SWSURFACE, 32, 32, 32, RED_MASK,GREEN_MASK,BLUE_MASK,ALPHA_MASK);
            SDL_FillRect(bg, NULL, SDL_MapRGBA(data->windowSurface->format, 0,0,0, SDL_ALPHA_TRANSPARENT));
            SDL_Color black = {0, 0, 0};
            SDL_Surface *text = SDL_SurfaceText("../Sans.ttf", "S", 38, &black);
            SDL_Rect rect2;
            rect2.x = (32 - (text->clip_rect).w)/2;
            rect2.y = (32 - (text->clip_rect).h)/2;
            SDL_BlitSurface(text, NULL, bg, &rect2);
            SDL_SetWindowIcon(data->window, bg);

            //Libération des surfaces et textures associées
            SDL_FreeSurface(bg);
            SDL_FreeSurface(text);

            //Récupération du renderer
            data->renderer = NULL;
            data->renderer = (SDL_CreateRenderer(data->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

            data->lastHovered = NULL;
            data->lastClicked = NULL;
            data->pencilMarkMode = 0;
            data->emptyCell = 81;

            //Message d'erreur
            if( data->renderer == NULL ) {
                fprintf(stderr, "Le renderer n'a pas pu etre cree ! SDL_eror : %s\n", SDL_GetError());
                succes = 0;
            }
        }
    }

    return succes;
}