//
// Created by TheRolf on 21/05/2019.
//

#include "sdl_sudoku.h"

extern sudokuGrid *data;
extern SDL_Color SDL_lightred;
extern SDL_Color SDL_blue;
extern SDL_Color SDL_white;
extern SDL_Color SDL_black;
extern SDL_Color SDL_grey;
extern SDL_Color SDL_lightgrey;

void printRed(cell *selectedCell) {
    //Fonction permettant d'afficher un fond rouge pour une cellule

    //Calcul de la postion du fond
    SDL_Rect rect;
    rect.y = GRID_HOVER_BORDER + GRID_MARGIN + selectedCell->column/3*GRID_THICK_BORDER + selectedCell->column * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->column - selectedCell->column/3);
    rect.x = GRID_HOVER_BORDER + GRID_MARGIN + selectedCell->line/3*GRID_THICK_BORDER + selectedCell->line * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->line - selectedCell->line/3);

    //Calcul de le taille du fond
    rect.w = GRID_CELL_SIZE - 2*GRID_HOVER_BORDER;
    rect.h = GRID_CELL_SIZE - 2*GRID_HOVER_BORDER;

    //Dessin du fond
    SDL_SetRenderDrawColorStruct(data->renderer, &SDL_lightred);
    SDL_RenderFillRect(data->renderer, &rect);

    //Dessin du nombre
    drawNumberAtPosition(selectedCell);
}

void printRect(cell* selectedCell, SDL_Color *color) {
    //Fonction affichant un cadre à l'intérieur de la cellule indiquée

    //Calcul de la postion du cadre
    SDL_Rect rect;
    rect.y = GRID_MARGIN + selectedCell->column/3*GRID_THICK_BORDER + selectedCell->column * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->column - selectedCell->column/3);
    rect.x = GRID_MARGIN + selectedCell->line/3*GRID_THICK_BORDER + selectedCell->line * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->line - selectedCell->line/3);
    //Calcul de la taille du cadre
    rect.w = GRID_CELL_SIZE;
    rect.h = GRID_CELL_SIZE;

    SDL_SetRenderDrawColorStruct(data->renderer, color); //Définition de la couleur du cadre
    int i;
    for (i = 0; i < GRID_HOVER_BORDER; i++) { //Affichage du cadre
        SDL_RenderDrawRect(data->renderer, &rect);
        rect.x++;
        rect.y++;
        rect.w -= 2;
        rect.h -= 2;
    }
}

void printHover(cell* selectedCell) {
    //Fonction permettant de mettre une cellule en surbrillance

    printRect(selectedCell, &SDL_blue);
}

void removeHover(cell* selectedCell) {
    //Fonction permettant qu'une celllule ne soit plus en surbrillance

    printRect(selectedCell, &SDL_white);
}

void drawNumberAtPosition(cell *number) {
    //Fonction permettant d'afficher un nombre dans une cellule

    if (number->number != EMPTY_VALUE) { //Si la case contient un nombre
        SDL_Rect rect;

        SDL_Surface *surfaceText = NULL; //Création de la surface

        char *string = convertInt(number->number); //Conversion du nombre en chaine de caractère

        tryInitGridFont(); //Initialisation de la police d'écriture

        surfaceText = TTF_RenderText_Solid(data->font, string, (number->isReadOnly) ? SDL_grey : SDL_black); //Dessin du nombre (en gris si c'est une donnée et noir si il est écrit par le joueur)

        if (surfaceText != NULL) { //Si le texte à réussit à être rendu

            SDL_Texture *texture = SDL_CreateTextureFromSurface(data->renderer, surfaceText); //Création de la surface associée

            //Calcul de la position et des dimensions du renctagle
            rect.y = GRID_MARGIN + number->column/3*GRID_THICK_BORDER + number->column * GRID_CELL_SIZE + GRID_THIN_BORDER * (number->column - number->column/3);  //controls the rect's x coordinate
            rect.x = GRID_MARGIN + number->line/3*GRID_THICK_BORDER + number->line * GRID_CELL_SIZE + GRID_THIN_BORDER * (number->line - number->line/3); // controls the rect's y coordinate
            rect.w = GRID_FONT_SIZE;
            rect.h = GRID_FONT_SIZE;

            SDL_Rect *fitRect = SDL_RectFit(&rect, surfaceText); //Ajustement de la surface pour correspondre à la taille de la cellule

            SDL_RenderCopy(data->renderer, texture, NULL, fitRect); //Affichage

            //Libération de la mémoire
            SDL_DestroyTexture(texture);
            free(fitRect);
        }

        //Libération de la surface
        SDL_FreeSurface(surfaceText);

        free(string);
    }
}


void drawNumberButtonsBackground(SDL_Color *color) {
    //Fonction permettant d'afficher le fond de la zone affichant les restrictions

    SDL_Rect rect = {GRID_MARGIN, GRID_SIZE + 2*GRID_MARGIN, GRID_SIZE, GRID_CELL_SIZE}; //Calcul de la postion et des dimensions
    SDL_SetRenderDrawColorStruct(data->renderer, color); //Application de la couleur
    SDL_RenderFillRect(data->renderer, &rect); //Affichage
}

void drawAvailableNumbers() {
    //Fonction permettant d'afficher les restrictions s'impsant à une cellule

    //Calcul de la postion et des dimensions
    SDL_Rect rect;
    rect.y = GRID_MARGIN*2 + GRID_SIZE;
    rect.x = GRID_MARGIN;
    rect.w = GRID_CELL_SIZE;
    rect.h = GRID_CELL_SIZE;

    rect.x += (GRID_SIZE - 9*GRID_CELL_SIZE)/2; //Centrage de la zone sur l'axe x

    tryInitGridFont(); //Initialisation de la police

    SDL_Surface *surface;
    SDL_Texture *texture;

    int i;
    for (i = 0; i < 9; i++) {

        char *number = convertInt(i+1); //Conversion des nombres en chaine de caractère
        surface = TTF_RenderText_Solid(data->font, number, (data->lastClicked->rules[i]==NULL) ? SDL_black : SDL_white); //Affichage en blanc pour les nombres interdits et en noir pour ceux autorisés

        texture = SDL_CreateTextureFromSurface(data->renderer, surface); //Création de la texture associée

        SDL_Rect *fit = SDL_RectFit(&rect, surface); //Ajustement de la surface dans la zone
        SDL_RenderCopy(data->renderer, texture, NULL, fit); //Affichage à l'écran

        //Libération de la mémoire
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        free(fit);

        rect.x += GRID_CELL_SIZE; //Décalage de l'abscisse pour afficher le prochaine
    }
}

void drawNumberBackground(cell* selectedCell) {
    //Fonction permettant d'afficher le fond d'une cellule

    //Calcul de la postion et de dimensions d'un cellule
    SDL_Rect rect;
    rect.y = GRID_HOVER_BORDER + GRID_MARGIN + selectedCell->column/3*GRID_THICK_BORDER + selectedCell->column * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->column - selectedCell->column/3);
    rect.x = GRID_HOVER_BORDER + GRID_MARGIN + selectedCell->line/3*GRID_THICK_BORDER + selectedCell->line * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->line - selectedCell->line/3);
    rect.w = GRID_CELL_SIZE - 2*GRID_HOVER_BORDER;
    rect.h = GRID_CELL_SIZE - 2*GRID_HOVER_BORDER;

    SDL_SetRenderDrawColorStruct(data->renderer, &SDL_white); //Application de la couleur
    SDL_RenderFillRect(data->renderer, &rect); //Affichage
}
void drawPencilMark(cell* selectedCell, int value) {
    //Fonction affichant une annotation

    //Détermination de la dimension d'une annotation
    SDL_Rect rect;
    rect.y = GRID_MARGIN + selectedCell->column/3*GRID_THICK_BORDER + selectedCell->column * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->column - selectedCell->column/3);
    rect.x = GRID_MARGIN + selectedCell->line/3*GRID_THICK_BORDER + selectedCell->line * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->line - selectedCell->line/3);
    rect.w = GRID_CELL_SIZE/3;
    rect.h = GRID_CELL_SIZE/3;

    char *number = convertInt(value); //Converstion de "value" en chaine de caractère (prérequis à TTF_RenderText_Solid()
    SDL_Surface *mark = TTF_RenderText_Solid(data->font, number, SDL_lightgrey); //Dessin de l'annotation
    free(number); //Libération de la chaine de caractère
    SDL_Rect *fit = SDL_RectFit(&rect, mark); //Mise à l'échelle du dessin

    //Ajustement de la position de l'annotation au sein de la case
    fit->x += GRID_CELL_SIZE / 3 * ((value-1)%3);
    fit->y += GRID_CELL_SIZE / 3 * ((value-1)/3);

    SDL_Texture *markTexture = SDL_CreateTextureFromSurface(data->renderer, mark); //Création de la texture associée (permet d'utiliser la carte graphique de l'ordinateur)
    SDL_FreeSurface(mark); //Libération de de la surface
    SDL_RenderCopy(data->renderer, markTexture, NULL, fit); //Affichage de la texture
    SDL_DestroyTexture(markTexture); //Libération de la texture
    free(fit); //Libération du rectangle de mise à l'échelle
}

void removePencilMark(cell* selectedCell, int value) {
    //Fonction éffaçant une annotation (fonctionnement similaire à drawPencilMark mais affiche un carré blanc)

    SDL_Rect rect;
    rect.y = GRID_MARGIN + selectedCell->column/3*GRID_THICK_BORDER + selectedCell->column * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->column - selectedCell->column/3);
    rect.x = GRID_MARGIN + selectedCell->line/3*GRID_THICK_BORDER + selectedCell->line * GRID_CELL_SIZE + GRID_THIN_BORDER * (selectedCell->line - selectedCell->line/3);
    rect.w = GRID_CELL_SIZE/3;
    rect.h = GRID_CELL_SIZE/3;

    char *number = convertInt(value);
    SDL_Surface *mark = TTF_RenderText_Solid(data->font, number, SDL_white);
    free(number);
    SDL_Rect *fit = SDL_RectFit(&rect, mark);

    fit->x += GRID_CELL_SIZE / 3 * ((value-1)%3);
    fit->y += GRID_CELL_SIZE / 3 * ((value-1)/3);

    SDL_Texture *markTexture = SDL_CreateTextureFromSurface(data->renderer, mark);
    SDL_FreeSurface(mark);
    SDL_RenderCopy(data->renderer, markTexture, NULL, fit);
    SDL_DestroyTexture(markTexture);
    free(fit);
}