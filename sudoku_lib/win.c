//
// Created by TheRolf on 13/05/2019.
//

#include "sdl_sudoku.h"

extern sudokuGrid *data;
extern SDL_Color SDL_lightgrey;
extern SDL_Color SDL_black;
void win() {
    //Fonction affichant un message de victoire

    SDL_SetWindowPosition(data->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED); //Centrage de la fenêtre au milieu de l'écran

    tryInitGridFont(); //Initialisation de la police

    SDL_Surface *bravo = TTF_RenderText_Solid(data->font, "Bravo !", SDL_black); //Création d'un texte
    SDL_Texture *bravoTexture = SDL_CreateTextureFromSurface(data->renderer, bravo); //Ajout du texte à la texture associée

    SDL_Surface *youWonSurface = TTF_RenderText_Solid(data->font, "Tu as gagne !", SDL_black); //Création d'un texte
    SDL_Texture *youWon = SDL_CreateTextureFromSurface(data->renderer, youWonSurface); //Ajout du texte

    SDL_Surface *autoDestroySurface = TTF_RenderText_Solid(data->font, "Maintentant je vais m'auto-detruire dans 3s", SDL_black); //Création d'un texte
    SDL_Texture *autoDestroy = SDL_CreateTextureFromSurface(data->renderer, autoDestroySurface); //Ajout du texte

    //Dimensionnement de la fenêtre
    SDL_SetWindowSize(data->window, autoDestroySurface->w + 2*GRID_MARGIN, 2*GRID_MARGIN + bravo->h + youWonSurface->h + autoDestroySurface->h);
    data->windowSurface = SDL_GetWindowSurface(data->window);

    //Application de la couleur de fond
    SDL_SetRenderDrawColorStruct(data->renderer, &SDL_lightgrey);
    SDL_RenderFillRect(data->renderer, NULL);

    //Calcul des dimensions et postion pour les différents textes
    SDL_Rect bravoRect;
    bravoRect.x = (2*GRID_MARGIN + autoDestroySurface->w - bravo->w)/2;
    bravoRect.y = (data->windowSurface->h - bravo->h - youWonSurface->h - autoDestroySurface->h)/2;
    bravoRect.h = bravo->h;
    bravoRect.w = bravo->w;

    SDL_Rect youWonRect;
    youWonRect.x = (2*GRID_MARGIN + autoDestroySurface->w - youWonSurface->w)/2;
    youWonRect.y = bravoRect.y + bravoRect.h;
    youWonRect.w = youWonSurface->w;
    youWonRect.h = youWonSurface->h;

    SDL_Rect autoDestroyRect;
    autoDestroyRect.x = (2*GRID_MARGIN + autoDestroySurface->w - autoDestroySurface->w)/2;
    autoDestroyRect.y = youWonRect.y+ youWonRect.h;
    autoDestroyRect.w = autoDestroySurface->w;
    autoDestroyRect.h = autoDestroySurface->h;

    //Ajout des textures dans l'objet à afficher
    SDL_RenderCopy(data->renderer, bravoTexture, NULL, &bravoRect);
    SDL_RenderCopy(data->renderer, youWon, NULL, &youWonRect);
    SDL_RenderCopy(data->renderer, autoDestroy, NULL, &autoDestroyRect);

    SDL_RenderPresent(data->renderer); //Affichage des texts

    //Libération de la mémoire
    SDL_FreeSurface(bravo);
    SDL_DestroyTexture(bravoTexture);
    SDL_FreeSurface(youWonSurface);
    SDL_DestroyTexture(youWon);
    SDL_FreeSurface(autoDestroySurface);
    SDL_DestroyTexture(autoDestroy);

    // attendre pendant trois secondes
    SDL_SetRenderDrawColorStruct(data->renderer, &SDL_lightgrey);
    for(int i = 0; i < 3; i++) { //Boucle afficahnt le compte à rebours

        SDL_RenderFillRect(data->renderer, &autoDestroyRect); //Dessin du fond

        //Changement du chiffre à afficher
        char phrase[TAILLE_MAX] = "";
        strcat(phrase, "Maintenant je vais m'auto-detruire dans " );
        char *countdown = convertInt(3-i);
        strcat(phrase, countdown);
        free(countdown);
        strcat(phrase, "s");

        //Application du nouveau texte
        autoDestroySurface =TTF_RenderText_Solid(data->font, phrase, SDL_black);
        autoDestroy = SDL_CreateTextureFromSurface(data->renderer, autoDestroySurface);

        autoDestroyRect.x = (data->windowSurface->w - autoDestroySurface->w)/2 - GRID_MARGIN; //Calcul de la postion

        SDL_RenderCopy(data->renderer, autoDestroy, NULL, &autoDestroyRect);

        SDL_RenderPresent(data->renderer); //Affichage du texte

        SDL_FreeSurface(autoDestroySurface);
        SDL_DestroyTexture(autoDestroy);

        SDL_Delay(1000); //Attente d'une seconde
    }
}

