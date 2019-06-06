#include <stdio.h>
#include <stdlib.h>
#include "sdl_custom_lib.h"
#include <SDL2/SDL_ttf.h>

int loadMedia(SDL_Surface **surface, char *location) {
    int success = 1;

    *surface = SDL_LoadBMP(location);
    if (*surface == NULL) {
        fprintf(stderr, "Unable to open %s : SDL error : %s", location, SDL_GetError());
        success = 0;
    }

    return success;
}

void freeSurface(SDL_Surface **surface) {
    SDL_FreeSurface(*surface);
}

void destroyAndQuit(SDL_Window **window) {
    SDL_DestroyWindow(*window);

    SDL_Quit();
}

void SDL_RectPrint(SDL_Rect *rect) {
    if (rect != NULL) {
        printf("w : %d\n", rect->w);
        printf("h : %d\n", rect->h);
        printf("x : %d\n", rect->x);
        printf("y : %d\n", rect->y);
    } else {
        printf("NULL");
    }
}

SDL_Rect *SDL_RectFit(SDL_Rect *rect, SDL_Surface *surface) {
    SDL_Rect *surfaceRect = &(surface->clip_rect);

    if ((float) surfaceRect->w == 0 || (float) surfaceRect->h == 0) {
        fprintf(stderr, "rect with null dim");
        return rect;
    }

    float widthRatio  = rect->w / ((float) surfaceRect->w);
    float heightRatio = rect->h / ((float) surfaceRect->h);

    // choose the bigger one
    SDL_Rect *newRect = malloc(sizeof(SDL_Rect));
    if (widthRatio < heightRatio) {
        //resize to width ratio
        newRect->w = rect->w;
        newRect->h = surfaceRect->h * widthRatio;
    } else {
        newRect->w = surfaceRect->w * heightRatio;
        newRect->h = rect->h;
    }

    // center position
    newRect->x = (rect->w - newRect->w)/2 + rect->x;
    newRect->y = (rect->h - newRect->h)/2 + rect->y;

    return newRect;
}

void SDL_ColorFromHex(SDL_Color *color, int hexValue) {
    color->a = 0xFF;
    color->r = ((hexValue >> 16) & 0xFF) / 255.0;  // Extract the RR byte
    color->g = ((hexValue >> 8) & 0xFF) / 255.0;   // Extract the GG byte
    color->b = ((hexValue) & 0xFF) / 255.0;        // Extract the BB byte
}

void SDL_SetRenderDrawColorStruct(SDL_Renderer *renderer, SDL_Color *color) {
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
}

SDL_Surface *SDL_SurfaceText(char *fontPath, char *string, int ptsize, SDL_Color *color) {
    TTF_Init();

    TTF_Font *font = TTF_OpenFont(fontPath, ptsize);
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, string, *color);

    return surfaceMessage;
}