//
// Created by TheRolf on 08/05/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "sdl_sudoku.h"
#include "initializeSudoku.h"

int initializeSudoku(sudokuGrid *grid) {
    int succes = 1;

    //On initialise SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
        fprintf(stderr, "SDL n'a pas pu etre initialise ! SDL_Error: %s\n", SDL_GetError() );
        succes = 0;
    }
    else {
        //On créé la fenêtre
        grid->window = NULL;
        grid->window = SDL_CreateWindow( "Smart Sudoku", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GRID_SIZE + 2*GRID_MARGIN, GRID_SIZE + 3*GRID_MARGIN + GRID_BOTTOMSPACE, SDL_WINDOW_SHOWN );
        if( grid->window == NULL ) {
            fprintf(stderr, "La fenetre n'a pas pu etre cree ! SDL_Error: %s\n", SDL_GetError());
            succes = 0;
        }
        else {
            //On récupère la surface de la fenêtre
            grid->windowSurface = SDL_GetWindowSurface( grid->window );

            // on initialise la police d'écriture
            tryInitGridFont(grid);

            // on change l'icône
            SDL_Surface *bg = SDL_CreateRGBSurface( SDL_SWSURFACE, 32, 32, 32, RED_MASK,GREEN_MASK,BLUE_MASK,ALPHA_MASK);
            SDL_FillRect(bg, NULL, SDL_MapRGBA(grid->windowSurface->format, 0,0,0, SDL_ALPHA_TRANSPARENT));
            SDL_Color black = {0, 0, 0};
            SDL_Surface *text = SDL_SurfaceText("../Sans.ttf", "S", 38, &black);
            SDL_Rect rect2;
            rect2.x = (32 - (text->clip_rect).w)/2;
            rect2.y = (32 - (text->clip_rect).h)/2;
            SDL_BlitSurface(text, NULL, bg, &rect2);
            SDL_SetWindowIcon(grid->window, bg);

            // on libère les surfaces et textures associées
            SDL_FreeSurface(bg);
            SDL_FreeSurface(text);

            //On récupère le renderer
            grid->renderer = NULL;
            grid->renderer = (SDL_CreateRenderer(grid->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

            if( grid->renderer == NULL ) {
                fprintf(stderr, "Le renderer n'a pas pu etre cree ! SDL_eror : %s\n", SDL_GetError());
                succes = 0;
            }
        }
    }

    return succes;
}