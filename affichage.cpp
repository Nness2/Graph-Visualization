#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <random>
#include <chrono>
#include <SDL/SDL.h>
#include "affichage.h" 
#include "visu.h"

void initSDL(SDL_Surface** screen)
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Erreur à l'initialisation de la SDL : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
 
  atexit(SDL_Quit);
  *screen = SDL_SetVideoMode(1000, 1000, 32, SDL_HWSURFACE);
  SDL_FillRect(*screen, NULL, SDL_MapRGB((*screen)->format, 0, 0, 0x80));
  if (*screen == NULL) {
    fprintf(stderr, "Impossible d'activer le mode graphique : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  SDL_WM_SetCaption("Visualisation de graph", NULL);
}

void attendreTouche(void)
{
  SDL_Event event;
 
  do
    SDL_WaitEvent(&event);
  while (event.type != SDL_QUIT && event.type != SDL_KEYDOWN);
}


void echangerEntiers(int* x, int* y)
{
  int t = *x;
  *x = *y;
  *y = t;
}
 
void setPixel(int x, int y, Uint32 coul, SDL_Surface* screen)
{
  *((Uint32*)(screen->pixels) + x + y * screen->w) = coul;
}


void setPixelVerif(int x, int y, Uint32 coul, SDL_Surface* screen)
{
  if (x >= 0 && x < screen->w &&
      y >= 0 && y < screen->h)
    setPixel(x, y, coul, screen);
}



void ligne(int x1, int y1, int x2, int y2, SDL_Surface* screen)
{
  int d, dx, dy, aincr, bincr, xincr, yincr, x, y;
  Uint32 coul =  SDL_MapRGB(screen->format, 0xFF, 0xFF, 0x00);
  if (abs(x2 - x1) < abs(y2 - y1)) {
    /* parcours par l'axe vertical */
 
    if (y1 > y2) {
      echangerEntiers(&x1, &x2);
      echangerEntiers(&y1, &y2);
    }
 
    xincr = x2 > x1 ? 1 : -1;
    dy = y2 - y1;
    dx = abs(x2 - x1);
    d = 2 * dx - dy;
    aincr = 2 * (dx - dy);
    bincr = 2 * dx;
    x = x1;
    y = y1;
 
    setPixelVerif(x, y, coul, screen);
 
    for (y = y1+1; y <= y2; ++y) {
      if (d >= 0) {
	x += xincr;
	d += aincr;
      } else
	d += bincr;
 
      setPixelVerif(x, y, coul, screen);
    }
 
  } else {
    /* parcours par l'axe horizontal */
    
    if (x1 > x2) {
      echangerEntiers(&x1, &x2);
      echangerEntiers(&y1, &y2);
    }
 
    yincr = y2 > y1 ? 1 : -1;
    dx = x2 - x1;
    dy = abs(y2 - y1);
    d = 2 * dy - dx;
    aincr = 2 * (dy - dx);
    bincr = 2 * dy;
    x = x1;
    y = y1;
 
    setPixelVerif(x, y, coul, screen);
 
    for (x = x1+1; x <= x2; ++x) {
      if (d >= 0) {
	y += yincr;
	d += aincr;
      } else
	d += bincr;
 
      setPixelVerif(x, y, coul, screen);
    }
  }    
}



void ligneHorizontale(int x, int y, int w, Uint32 coul, SDL_Surface* screen){
  SDL_Rect r;
 
  r.x = x;
  r.y = y;
  r.w = w;
  r.h = 1;
 
  SDL_FillRect(screen, &r, coul);
}


void cercle(int cx, int cy, int rayon, SDL_Surface* screen){
  int d, y, x;
  Uint32 coul =  SDL_MapRGB(screen->format, 0xFF, 0xFF, 0x00);
  d = 3 - (2 * rayon);
  x = 0;
  y = rayon;
 
  while (y >= x) {
    ligneHorizontale(cx - x, cy - y, 2 * x + 1, coul, screen);
    ligneHorizontale(cx - x, cy + y, 2 * x + 1, coul, screen);
    ligneHorizontale(cx - y, cy - x, 2 * y + 1, coul, screen);
    ligneHorizontale(cx - y, cy + x, 2 * y + 1, coul, screen);
 
    if (d < 0)
      d = d + (4 * x) + 6;
    else {
      d = d + 4 * (x - y) + 10;
      y--;
    }
 
    x++;
  }
}
