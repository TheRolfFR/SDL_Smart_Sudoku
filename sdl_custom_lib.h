#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

int loadMedia(SDL_Surface**, char*);

void SDL_RectPrint(SDL_Rect*);

SDL_Rect *SDL_RectFit(SDL_Rect*, SDL_Surface*);

void SDL_ColorFromHex(SDL_Color*, int);

void SDL_SetRenderDrawColorStruct(SDL_Renderer*, SDL_Color*);

struct SDL_Surface *SDL_SurfaceText(char*, char*, int, SDL_Color*);

void destroyAndQuit(SDL_Window**);