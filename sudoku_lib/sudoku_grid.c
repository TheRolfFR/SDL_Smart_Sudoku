//
// Created by TheRolf on 03/05/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../sdl_custom_lib.h"
#include "sdl_sudoku.h"

void tryInitGridFont(sudokuGrid *grid) {
    TTF_Font *Sans = TTF_OpenFont("../Sans.ttf", GRID_FONT_SIZE);
    grid->font = Sans;
}

int loadGrid(cell* tab[][9], char *path, int numberOfFiles) {
    srand(time(0));
    int index = rand()%numberOfFiles;

    char totalpath[TAILLE_MAX];
    strcpy(totalpath, path);
    strcat(totalpath, "grid");
    strcat(totalpath, convertInt(index));
    strcat(totalpath, ".txt");

    FILE *file = NULL;
    file = fopen(totalpath, "r");

    cell *myCell;
    if(file != NULL) {
        char line[TAILLE_MAX] = "";
        int l = 0, c;
        while(fgets(line, TAILLE_MAX, file)) {
            c = 0;

            // while line did not end add the cell values
            while(line[c*2] != 0 && c < 9) {
                tab[l][c] = initCell(l, c, (line[c*2] != ' ') ? line[c*2] - '0' : -1, 0, 0);

                c++;
            }

            // if line finished before
            if(c < 9) {
                // add the other ones
                for(c = c; c < 9; c++) {
                    myCell = malloc(sizeof(cell));
                    myCell->isHovered = 0;
                    myCell->isClicked=0;
                    myCell->line = l;
                    myCell->column = c;
                    myCell->number = -1;

                    tab[l][c] = myCell;
                }
            }

            // reset totally the line string with zeros
            memset(line,0,strlen(line));
            l++;
        }

        fclose(file);
        return 0;
    } else {
        fprintf(stderr, "Impossible to open %s\n", totalpath);
    }
    return -1;
}

sudokuGrid *initGrid(SDL_Window **window, SDL_Surface **windowSurface, SDL_Renderer **renderer) {
    // parameters to tweak
    sudokuGrid *grid = malloc(sizeof(sudokuGrid));
    SDL_Color background, black = {0,0,0}, lightblue = {0x4D, 0xD0, 0xE1}, blue, white = {255, 255, 255};
    SDL_ColorFromHex(&blue, 0x01579B);

    // colors
    grid->hoverBackgroundColor = lightblue;
    grid->clickBackgroundColor = blue;
    grid->black = black;
    grid->white = white;

    // window
    grid->window = *window;
    grid->windowSurface = *windowSurface;
    grid->renderer = *renderer;

    grid->lastNumberUpdated = NULL;

    // intialize font
    tryInitGridFont(grid);

    // setting window size
    SDL_SetWindowSize(grid->window, GRID_SIZE + 2*GRID_MARGIN, GRID_SIZE + 3*GRID_MARGIN + GRID_BOTTOMSPACE);
    SDL_SetWindowTitle(grid->window, "Smart Sudoku");

    //setting icon
    SDL_Surface *bg = SDL_CreateRGBSurface( SDL_SWSURFACE, 32, 32, 32, RED_MASK,GREEN_MASK,BLUE_MASK,ALPHA_MASK);
    SDL_FillRect(bg, NULL, SDL_MapRGBA(grid->windowSurface->format, 0,0,0, SDL_ALPHA_TRANSPARENT));
    SDL_Surface *text = SDL_SurfaceText("../Sans.ttf", "S", 38, &black);
    SDL_Rect rect2;
    rect2.x = (32 - (text->clip_rect).w)/2;
    rect2.y = (32 - (text->clip_rect).h)/2;
    SDL_BlitSurface(text, NULL, bg, &rect2);
    SDL_SetWindowIcon(grid->window, bg);

    SDL_FreeSurface(bg);
    SDL_FreeSurface(text);

    return grid;
}

void drawSudokuGrid(sudokuGrid *grid)  {
    SDL_RenderClear(grid->renderer);

    SDL_Color lightgrey = {189,189,189}, white = {255,255,255}, grey = {158,158,158};

    // drawing background
    SDL_SetRenderDrawColorStruct(grid->renderer, &lightgrey);
    SDL_RenderFillRect(grid->renderer, NULL);

    // drawing background of the grid
    SDL_SetRenderDrawColorStruct(grid->renderer, &white);
    SDL_Rect rect = {GRID_MARGIN, GRID_MARGIN, GRID_SIZE, GRID_SIZE};
    SDL_RenderFillRect(grid->renderer, &rect);

    // draw thin borders
    SDL_SetRenderDrawColorStruct(grid->renderer, &grey);
    int i, offset;
    for(i = 0; i < 6; i++) {
        offset = (i+ 1 + i / 2)*GRID_CELL_SIZE + i*GRID_THIN_BORDER + i/2*GRID_THICK_BORDER + GRID_MARGIN;

        //vertical
        SDL_RenderDrawLine(grid->renderer, offset, GRID_MARGIN, offset, GRID_MARGIN + GRID_SIZE);

        // horizontal
        SDL_RenderDrawLine(grid->renderer, GRID_MARGIN, offset, GRID_MARGIN + GRID_SIZE, offset);
    }

    // draw thick borders
    SDL_SetRenderDrawColorStruct(grid->renderer, &grey);
    SDL_Rect vert = {0, GRID_MARGIN, GRID_THICK_BORDER, GRID_SIZE}, hori = {GRID_MARGIN, 0, GRID_SIZE, GRID_THICK_BORDER};
    for(i = 0; i < 2; i++) {
        offset = 3*(1+i)*GRID_CELL_SIZE + 2*(i+1)*GRID_THIN_BORDER + GRID_MARGIN + i * GRID_THICK_BORDER;
        vert.x = offset;
        hori.y = offset;

        // vertical
        SDL_RenderFillRect(grid->renderer, &vert);
        SDL_RenderFillRect(grid->renderer, &hori);
    }
}