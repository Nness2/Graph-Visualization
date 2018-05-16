#ifndef VISU_H___
#define VISU_H___

#include <SDL/SDL.h>
using std::vector;

class noeud {
	public:

	int id;
	int x;
	int y;
	vector <int> connexions;	
 	//int forcex
 	//int forcey

	noeud (){};

	noeud (int id, int x, int y, vector <int> connexions){
		this->id = id;
   		this->x = x;
   		this->y = y;
    	this->connexions = connexions;
	}
};

vector <noeud> creatGraphAlea();
vector <noeud> creatGraph();
void afficheGraph (vector <noeud> graph, SDL_Surface* screen);
void visualisation (SDL_Surface** screen, vector <noeud> *graph);

#endif