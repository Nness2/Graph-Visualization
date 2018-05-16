#ifndef AFFICHAGE_H___
#define AFFICHAGE_H___

#include <SDL/SDL.h>

void attendreTouche(void);
void initSDL(SDL_Surface** screen);
void ligne(int x1, int y1, int x2, int y2, SDL_Surface* screen);
void cercle(int cx, int cy, int rayon, SDL_Surface* screen);
#endif