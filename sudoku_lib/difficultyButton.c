//
// Created by TheRolf on 25/05/2019.
//

#include "sdl_sudoku.h"

extern sudokuGrid* data;
extern SDL_Color SDL_white;
extern SDL_Color SDL_black;
void fillAndDrawButton(difficultyButton* button, char text[]) {
    // creation du rect
    SDL_Rect r;
    r.x = button->x;
    r.y = BUTTON_Y_OFFSET;
    r.w = BUTTON_WIDTH;
    r.h = BUTTON_HEIGHT;

    //remplissage du fond
    SDL_SetRenderDrawColorStruct(data->renderer, &SDL_white);
    SDL_RenderFillRect(data->renderer, &r);

    // initialisation de la police
    tryInitGridFont();

    // creation du texte
    SDL_Surface *textSurface = TTF_RenderText_Solid(data->font, text, SDL_black);

    // creation d'un rect adapte a l'espace disponible
    SDL_Rect *fit = SDL_RectFit(&r, textSurface);

    // creation de la texture et rendu
    SDL_Texture *t = SDL_CreateTextureFromSurface(data->renderer, textSurface);
    SDL_RenderCopy(data->renderer, t, NULL, fit);
    SDL_RenderPresent(data->renderer);

    // nettoyage
    SDL_DestroyTexture(t);
    SDL_FreeSurface(textSurface);
    free(fit);
}

char isInButton(difficultyButton* button, int x, int y) {
    return (x > button->x && x < button->x + BUTTON_WIDTH && y > BUTTON_Y_OFFSET && y < BUTTON_Y_OFFSET + BUTTON_HEIGHT) ? 1 : 0;
}

void clickButton(difficultyButton* button) {
    button->previouslyClicked = 1;
}

void unclickButton(difficultyButton* button) {
    button->previouslyClicked = 1;
}

int handleDifficultyButtons() {
    int x, y;
    SDL_GetMouseState(&x, &y);

    if(x > data->easy->x && x < GRID_MARGIN + GRID_SIZE && y > BUTTON_Y_OFFSET && y < BUTTON_Y_OFFSET + BUTTON_HEIGHT) {
        if(isInButton(data->easy, x, y)) {
            if(data->easy->previouslyClicked) {
                return changeDifficulty("easy");
            } else {
                clickButton(data->easy);
            }
        }
        if(isInButton(data->normal, x, y)) {
            if(data->normal->previouslyClicked) {
                return changeDifficulty("normal");
            } else {
                clickButton(data->normal);
            }
        }
        if(isInButton(data->hard, x, y)) {
            if(data->hard->previouslyClicked) {
                return changeDifficulty("hard");
            } else {
                clickButton(data->hard);
            }
        }

        char title[TAILLE_MAX];
        strcpy(title, data->initialTitle); // copier-coller le texte
        strcat(title, " (RECLIQUER POUR CONFIRMER)"); // rajoute la confirmation
        SDL_SetWindowTitle(data->window, title);
    } else {
        ChangeTitleMode();
    }

    return 1;
}
int changeDifficulty(char dif[]) {
    unclickButton(data->easy);
    unclickButton(data->normal);
    unclickButton(data->hard);

    // on essaye de lire le fichier de difficulte
    FILE* file = NULL;
    file = fopen("difficulte.txt", "w");

    if(file != NULL) {
        // insertion de la difficulte
        fputs(dif, file);

        // fermeture du fichier
        fclose(file);
        return 0;
    }

    return 1;
}