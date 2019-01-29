/*!\file visu.cpp
 * \brief Traitement du graphe
 * \author Aness MENAA
 */

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

using std::vector;

/*!\brief Génère la position aléatoirement des noeuds
*  \param nalea Nombre de positions à généré
*  \return Retourne les valeurs aléatoire généré*/
vector<int> vectorConnexions(int nalea){
  //srand (time (NULL));

  std::default_random_engine generator; 
  std::uniform_int_distribution<int> distribution(1,3);

  vector <int> vconnex;

  int nbconnex = distribution(generator);
  
  int betnalea = distribution(generator);
  
  for(int i=0;i<nbconnex;i++){
    int betnalea = rand() %nalea+0;
    vconnex.push_back(betnalea);
  }
  return vconnex;
}

/*!\brief Temporisation de l'animation
*  \param i Limite de temps*/
void my_delay(int i){
    clock_t start,end;
    start=clock();
    while(((end=clock())-start)<=i);
}

/*!\brief Teste si le noeud est dans l'écran
*  \param x Position x du noeud
*  \param y Position y du noeud
*  \param screen Notre écran
*  \return Retourne 1 si le noeud est dans notre écran*/
int testInside (int x, int y, SDL_Surface* screen){
    if (x >= 0 && x < screen->w && y >= 0 && y < screen->h)
      return 1;
    return 0;
}


/*!\brief Teste si deux noeud sont proche l'un de l'autre
*  \param n1 Premier noeud à tester
*  \param n2 Deuxième noeud à tester
*  \return Retourne 1 si noeud 1 est proche de noeud 2*/
int proche (noeud* n1, noeud* n2){
  if (n2->x > (n1->x)-40 && n2->x < (n1->x)+40 && n2->y > (n1->y)-40 && n2->y < (n1->y)+40)
    return 1;
  return 0;
}

/*!\brief Fonction se chargent de rapprocher les deux noeuds mis en argument
*  \param n1 Premier noeud 
*  \param n2 Deuxième noeud
*  \param screen Notre écran
*/
void algRapprochement(noeud* n1, noeud* n2, SDL_Surface* screen){
    int a,b;
    a = (n2->x-n1->x) *0.1;
    b = (n2->y-n1->y) *0.1;
      n1->x += a;
      n1->y += b;
      n2->x -= a;
      n2->y -= b;
}
 

/*!\brief Fonction se chargent d'éloigner les deux noeuds mis en argument
*  \param n1 Premier noeud 
*  \param n2 Deuxième noeud
*  \param screen Notre écran
*/
void algEloignementProche(noeud* n1, noeud* n2, SDL_Surface* screen){
    int a,b;
    int x1, x2, y1, y2;
    a = (n2->x-n1->x) *0.40;
    b = (n2->y-n1->y) *0.40;
    x1 = n1->x - a;
    x2 = n2->x + a;
    y1 = n1->y - b;
    y2 = n2->y + b;
    if (testInside (x1, y1, screen) == 1){
      n1->x -= a;
      n1->y -= b;   
    }
    if (testInside (x2, y2, screen) == 1){
      n2->x += a;
      n2->y += b;  
    }   
}


/*!\brief Calcule l'attaction entre deux noeuds
*  \param n1 Premier noeud 
*  \param n2 Deuxième noeud
*  \param screen Notre écran
*/
int attraction (noeud* n1, noeud* n2, SDL_Surface* screen){
  for (int i = 0; i < n1->connexions.size(); ++i){
    if (n1->connexions[i] == n2->id){
      algRapprochement(n1,n2, screen);
      return 0;
    }
  }
}

/*!\brief Calcule la répultion entre deux noeuds
*  \param n1 Premier noeud 
*  \param n2 Deuxième noeud
*  \param screen Notre écran
*/
int repultionProche (noeud* n1, noeud* n2, SDL_Surface* screen){
  for (int i = 0; i < n1->connexions.size(); ++i){
    if (n1->connexions[i] != n2->id){
      if (proche(n1, n2) == 1){
        algEloignementProche(n1,n2, screen);
        return 0;
      }
    }
  }
}

/*!\brief Génère un graphe aléatoire
*  \return Retourne la liste des positions de chaque noeuds généré aléatoirement*/
vector <noeud> creatGraphAlea(){ 
  srand (time (NULL));
  int nalea = rand() % 100 + 50;
   /* nombre de noeud */
  int canxmax  = rand() % 500;
   /* taille du canvas en x */
  int canymax  = rand() % 500; 
   /* taille du canvas en y */
  vector <noeud> graph;

  std::default_random_engine generator; 
  std::uniform_int_distribution<int> distribution(100,500);

  for(int i=0;i<=nalea;i++){
    int canxmax  = rand() % 1000+0;
    /* taille du canvas en x */
    int canymax  = rand() % 1000+0;
    graph.push_back(noeud (i,canxmax,canymax,vectorConnexions(nalea)));
    }

  return graph;
}

/*!\brief Création d'un Graphe de teste
*/
vector <noeud> creatGraph (){
  vector <noeud> graph;
  vector <int> v0;
  vector <int> v1;
  vector <int> v2;
  vector <int> v3;
  noeud n0(0, 200, 200, v0 = {1,3});
  noeud n1(1, 400, 200, v1 = {0,3,2});
  noeud n2(2, 200, 400, v2 = {1});
  noeud n3(3, 400, 400, v3 = {1,0});
  graph.push_back(n0);
  graph.push_back(n1);
  graph.push_back(n2);
  graph.push_back(n3);

  return graph;
}
 
/*!\brief Affichage de l'interface graphique
*  \param screen Notre écran
*  \param g La liste des noeuds 
*/
void afficheGraph (vector <noeud> graph, SDL_Surface* screen){
  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 15, 5, 90));
  for (int i = 0; i < graph.size(); ++i){
    cercle (graph[i].x, graph[i].y, 3, screen);
    for (int j = 0; j < graph[i].connexions.size(); ++j){
      ligne(graph[i].x, graph[i].y, graph[graph[i].connexions[j]].x, graph[graph[i].connexions[j]].y, screen);
    }
  }
  SDL_Flip(screen);
}

/*!\brief Calcule et mise à jour de l'interface graphique
*  \param screen Notre écran
*  \param g La liste des noeuds 
*/
void visualisation (SDL_Surface** screen, vector <noeud> *g){
  vector <noeud> graph = *g;

  for (int x = 0 ; x < 10 ; x++){
    for(int ww = 0 ; ww < 20 ; ww++){
      for (int i=0;i<graph.size();i++){ 
        for(int j=0;j<graph.size();j++){
          if (i != j)  
            attraction(&graph[i],&graph[j], *screen);
        }
      }
      /* boucle appliquant l'attraction pour chaque paire de noeuds */

      afficheGraph(graph, *screen);
      my_delay(9000);
    }
    for(int ww = 0 ; ww < 25 ; ww++){
      for (int i=0;i<graph.size();i++){ 
        for(int j=0;j<graph.size();j++){
          if (i != j)
            repultionProche(&graph[i],&graph[j], *screen);
        }
      }
      afficheGraph(graph, *screen);
      my_delay(7000);
    }
    /* boucle appliquant la répultion pour chaque paire de noeuds */


  }
}