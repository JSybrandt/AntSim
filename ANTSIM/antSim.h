#pragma once
#include "game.h"

#include "cstdlib"
#include "ctime"

#include "ant.h"
#include "colony.h"
#include "food.h"
#include "pheromone.h"
#include "mouse.h"

//for collision rect
#include<list>

namespace antSimNS
{
	const int MAX_PHEROMONE = 1000;
	const int MAX_ANTS = 100;
	const int MAX_FOOD = 100;
	const int STARTING_ANTS = 0;
	const int HOR_NUM_COL_RECTS = 10;
}

class AntSim: public Game
{
private:

	struct collisionRect
	{
		//to be used for non moving actors
		std::list<Actor*>objects;
		std::list<Ant*>ants;

		collisionRect();
		//~collisionRect(){};

		void addActor(Actor* in);
		void addAnt(Ant* in);

		void checkCollisions();
		void clear();

	};

	TextDX debugText;
	TextureManager antTex;
	TextureManager hillTex;
	TextureManager foodTex;
	TextureManager pherTex;
	Ant ants[antSimNS::MAX_ANTS];
	Food food[antSimNS::MAX_FOOD];
	Pheromone pheromones[antSimNS::MAX_PHEROMONE];
	Colony blackBase;
	Colony redBase;
	Mouse mouse;
	int antIndex;
	int foodIndex;
	int pherIndex;

	bool clickedLastFrame; 

	float rectWidth;
	float rectHeight;

	collisionRect colRects[antSimNS::HOR_NUM_COL_RECTS][antSimNS::HOR_NUM_COL_RECTS];

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

	Ant* spawnAnt(VECTOR2 loc, Species spc);
	Food* spawnFood(VECTOR2 loc);
	Pheromone* spawnPher(VECTOR2 loc, Signal s);

	//call for static objects once, call for ants every frame
	void placeObjectInProperRect(Actor* in);
	void placeAntObjectInProperRect(Ant* in);
};
