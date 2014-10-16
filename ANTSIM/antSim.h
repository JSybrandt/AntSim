#pragma once
#include "game.h"

#include "cstdlib"
#include "ctime"

#include "ant.h"
#include "colony.h"

namespace antSimNS
{
	const int MAX_ANTS = 10000;
	const int STARTING_ANTS = 100;
}

class AntSim: public Game
{
private:
	TextureManager antTex;
	TextureManager hillTex;
	Ant ants[antSimNS::MAX_ANTS];
	Colony base;
	int antIndex;

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
};
