//
// Created by TheRolf on 13/05/2019.
//

#include "sdl_sudoku.h"

extern sudokuGrid *data;
void win() {
    // on remet un fond grid
    SDL_Color lightgrey = {189,189,189};

    tryInitGridFont();

    SDL_Color black = {0, 0, 0};
    SDL_Surface *bravo = TTF_RenderText_Solid(data->font, "Bravo !", black);
    SDL_Texture *bravoTexture = SDL_CreateTextureFromSurface(data->renderer, bravo);

    SDL_Surface *youWonSurface = TTF_RenderText_Solid(data->font, "Tu as gagne !", black);
    SDL_Texture *youWon = SDL_CreateTextureFromSurface(data->renderer, youWonSurface);

    SDL_Surface *autoDestroySurface = TTF_RenderText_Solid(data->font, "Maintentant je vais m'auto-detruire dans 3s", black);
    SDL_Texture *autoDestroy = SDL_CreateTextureFromSurface(data->renderer, autoDestroySurface);

    // Retaille de la fenêtre
    SDL_SetWindowSize(data->window, autoDestroySurface->w + 2*GRID_MARGIN, 2*GRID_MARGIN + bravo->h + youWonSurface->h + autoDestroySurface->h);
    data->windowSurface = SDL_GetWindowSurface(data->window);

    // on rend le fond en gris clair
    SDL_SetRenderDrawColorStruct(data->renderer, &lightgrey);
    SDL_RenderFillRect(data->renderer, NULL);

    // calcul des rects

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

    // on copie le rendu des félicitations
    SDL_RenderCopy(data->renderer, bravoTexture, NULL, &bravoRect);
    // on copie le rendu du "tu as gagné !"
    SDL_RenderCopy(data->renderer, youWon, NULL, &youWonRect);
    // on copie le rendu de l'auto-destruction
    SDL_RenderCopy(data->renderer, autoDestroy, NULL, &autoDestroyRect);

    SDL_RenderPresent(data->renderer);

    SDL_FreeSurface(bravo);
    SDL_DestroyTexture(bravoTexture);
    SDL_FreeSurface(youWonSurface);
    SDL_DestroyTexture(youWon);
    SDL_FreeSurface(autoDestroySurface);
    SDL_DestroyTexture(autoDestroy);

    // attendre pendant trois secondes
    SDL_SetRenderDrawColorStruct(data->renderer, &lightgrey);
    for(int i = 0; i < 3; i++) {

        // Redessiner le fond grid sur la phrase
        SDL_RenderFillRect(data->renderer, &autoDestroyRect);

        // Redéfinir le texte
        char phrase[TAILLE_MAX] = "";
        strcat(phrase, "Maintenant je vais m'auto-detruire dans " );
        strcat(phrase, convertInt(3-i));
        strcat(phrase, "s");

        // reprint le texte
        autoDestroySurface =TTF_RenderText_Solid(data->font, phrase, black);
        autoDestroy = SDL_CreateTextureFromSurface(data->renderer, autoDestroySurface);

        autoDestroyRect.x = (data->windowSurface->w - autoDestroySurface->w)/2 - GRID_MARGIN;

        SDL_RenderCopy(data->renderer, autoDestroy, NULL, &autoDestroyRect);

        SDL_RenderPresent(data->renderer);

        SDL_Delay(1000);
    }
}

