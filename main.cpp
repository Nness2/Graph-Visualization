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

/*!\brief génére un graphe aléatoire
 * créé la fenêtre
 * transforme le graphe lorsqu'une touche est appuyé
 * ferme le programme lorsqu'une touche est appuyé une deuxième fois*/ 
int main(int argc, char const *argv[]){
  vector <noeud> graph = creatGraphAlea();
  SDL_Surface* screen;
  initSDL(&screen);
  /* Crée la fenêtre */
  afficheGraph(graph, screen);
  /* Affiche le graphe aléatoire non visualisable */
  attendreTouche();
  visualisation(&screen, &graph);
  /* Calcule la nouvelle position des noeuds et affiche le nouveau graphe visualisable */
  attendreTouche();
  return 0;
}

