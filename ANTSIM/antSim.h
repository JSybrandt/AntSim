#pragma once
#include "game.h"

#include "cstdlib"
#include "ctime"

#include "ant.h"
#include "colony.h"
#include "food.h"
#include "pheromone.h"
#include "mouse.h"

namespace antSimNS
{
	
	const int MAX_PHEROMONE = 2000;
	const int MAX_ANTS = 1000;
	const int MAX_FOOD = 1000;
	const int STARTING_ANTS = 10;
}

class AntSim: public Game
{
private:
	TextureManager antTex;
	TextureManager hillTex;
	TextureManager foodTex;
	TextureManager pherTex;
	Ant ants[antSimNS::MAX_ANTS];
	Food food[antSimNS::MAX_FOOD];
	Pheromone pheromones[antSimNS::MAX_PHEROMONE];
	Colony base;
	Mouse mouse;
	int antIndex;
	int foodIndex;
	int pherIndex;

	bool clickedLastFrame; 

public:
	
	AntSim();
	~AntSim();

	// Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();

	void spawnAnt(VECTOR2 loc);
	void spawnFood(VECTOR2 loc);
	void spawnPher(VECTOR2 loc, Signal s);
};
