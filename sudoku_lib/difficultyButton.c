//
// Created by TheRolf on 25/05/2019.
//

#include "sdl_sudoku.h"

extern sudokuGrid* data;
extern SDL_Color SDL_white;
extern SDL_Color SDL_black;
void fillAndDrawButton(difficultyButton* button, char text[]) {
    //Fonction affichant les boutons de difficulté

    //Création du rectangle
    SDL_Rect r;
    r.x = button->x;
    r.y = BUTTON_Y_OFFSET;
    r.w = BUTTON_WIDTH;
    r.h = BUTTON_HEIGHT;

    //Remplissage du fond
    SDL_SetRenderDrawColorStruct(data->renderer, &SDL_white);
    SDL_RenderFillRect(data->renderer, &r);

    //Initialisation de la police
    tryInitGridFont();

    //Création du texte
    SDL_Surface *textSurface = TTF_RenderText_Solid(data->font, text, SDL_black);

    //Création d'un rectangle adapte a l'espace disponible
    SDL_Rect *fit = SDL_RectFit(&r, textSurface);

    //Création de la texture et rendu
    SDL_Texture *t = SDL_CreateTextureFromSurface(data->renderer, textSurface);
    SDL_RenderCopy(data->renderer, t, NULL, fit);
    SDL_RenderPresent(data->renderer);

    //Nettoyage
    SDL_DestroyTexture(t);
    SDL_FreeSurface(textSurface);
    free(fit);
}

char isInButton(difficultyButton* button, int x, int y) {
    //Fonction retournant si la souris survole un bouton

    return (x > button->x && x < button->x + BUTTON_WIDTH && y > BUTTON_Y_OFFSET && y < BUTTON_Y_OFFSET + BUTTON_HEIGHT) ? 1 : 0;
}

void clickButton(difficultyButton* button) {
    //Fonction indiquant que le bouton à été cliqué

    button->previouslyClicked = 1;
}

void unclickButton(difficultyButton* button) {
    //Fonction indiquant que le bouton n'a pas été cliqué

    button->previouslyClicked = 0;
}

int handleDifficultyButtons() {
    //Fonction déterminant si il faut changer de difficulté

    int x, y;
    SDL_GetMouseState(&x, &y); //Obtention de la position de la souris

    if(x > data->easy->x && x < GRID_MARGIN + GRID_SIZE && y > BUTTON_Y_OFFSET && y < BUTTON_Y_OFFSET + BUTTON_HEIGHT) {
        if(isInButton(data->easy, x, y)) { //Si la souris survole le bouton "facile"
            if(data->easy->previouslyClicked) { //Si le bouton à déjà été cliqué
                return changeDifficulty("easy"); //Mets la difficulté sur facile
            } else { //Sinon
                clickButton(data->easy); //Indique que le bouton à été cliqué
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
        strcpy(title, data->initialTitle); //Copie du titre initial
        strcat(title, " (RECLIQUER POUR CONFIRMER)"); //Ajout de la mention "(RECLIQUER POUR CONFIRMER)"
        SDL_SetWindowTitle(data->window, title); //Mise en place du titre
    } else { //Si auncun bouton n'a été cliqué
        if(data->easy->previouslyClicked) {
            data->easy->previouslyClicked = 0; // Réinitialisation du bouton facile
        }
        if(data->normal->previouslyClicked) {
            data->normal->previouslyClicked = 0; // Réinitialisation du bouton normal
        }
        if(data->hard->previouslyClicked) {
            data->hard->previouslyClicked = 0; // Réinitialisation du bouton difficile
        }
        ChangeTitleMode(); //Réinitialisation du titre
    }

    return 1;
}
int changeDifficulty(char dif[]) {
    //Fonction changeant de difficulté

    unclickButton(data->easy);
    unclickButton(data->normal);
    unclickButton(data->hard);

    FILE* file = NULL;
    file = fopen("difficulte.txt", "w"); //Ouverture du fichier de difficulté

    if(file != NULL) {

        fputs(dif, file); //Ecriture de la difficulté

        fclose(file); //Fermeture du fichier
        data->difficultyChanged = 1; //Changement de difficulté demandé
        return 0;
    }

    return 1;
}