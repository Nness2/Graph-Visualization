#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <random>
#include <SDL/SDL.h>
#include <chrono>
#include "visu.h"
#include "affichage.h" 

  
int main(int argc, char const *argv[]){
  vector <noeud> graph = creatGraphAlea();
  SDL_Surface* screen;
	initSDL(&screen);
  afficheGraph(graph, screen);
  attendreTouche();

  visualisation(&screen, &graph);

  attendreTouche();
	return 0;
}

