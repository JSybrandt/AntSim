#pragma once
#include "game.h"

class AntSim: public Game
{
private:

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
};