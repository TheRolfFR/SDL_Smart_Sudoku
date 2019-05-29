//
// Created by TheRolf on 08/05/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sdl_sudoku.h"

//Constantes de masque NE PAS TOUCHER
#define RED_MASK   0xFF000000
#define GREEN_MASK 0x00FF0000
#define BLUE_MASK  0x0000FF00
#define ALPHA_MASK 0x000000FF

extern sudokuGrid *data;
int initializeSudoku() {
    //Fonction permettant d'initialiser le jeu

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

            //Initialisation des données
            data->lastHovered = NULL; //Pointeur vers la cellule en surbrillance
            data->lastClicked = NULL; //Pointeur vers la cellule sélectionnée
            data->pencilMarkMode = 0; //Indique l'activation du mode annotation
            data->redHover = 0; //Champs indiquant le nombre que contiennent les cases sur fond rouge
            data->lastKeyWasCtrl = 0; //Indique la nature du dernier appui clavier ou souris (ctrl ou non)
            data->typedNumber = 0; //Indique le nombre demandé
            data->save = NULL; //Liste des actions
            data->undoMode = 1; //Indique l'activation du mode "retour en arrière" (initialisé comme actif afin de ne pas enregistrer l'initialisation de la grille)
            data->difficultyChanged = 0; //Indique qu'un changement de difficulté a été demandé guillaume aled

            //Initialisation des boutons
            data->easy = malloc(sizeof(difficultyButton));
            data->easy->x = GRID_MARGIN;
            data->easy->previouslyClicked = 0;

            data->normal = malloc(sizeof(difficultyButton));
            data->normal->x = GRID_MARGIN + BUTTON_WIDTH;
            data->normal->previouslyClicked = 0;

            data->hard = malloc(sizeof(difficultyButton));
            data->hard->x = GRID_MARGIN + BUTTON_WIDTH*2;
            data->hard->previouslyClicked = 0;

            //Message d'erreur
            if( data->renderer == NULL ) {
                fprintf(stderr, "Le renderer n'a pas pu etre cree ! SDL_eror : %s\n", SDL_GetError());
                succes = 0;
            }
        }
    }

    return succes;
}