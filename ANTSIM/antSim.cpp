// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Game Engine Part 1
// Chapter 4 RedSpace.cpp v1.0
// RedSpace is the class we create.

#include "antSim.h"


//=============================================================================
// Constructor
//=============================================================================
AntSim::AntSim()
{
	srand((unsigned)time(0)); 
	antIndex = 0;
}

//=============================================================================
// Destructor
//=============================================================================
AntSim::~AntSim()
{
	releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void AntSim::initialize(HWND hwnd)
{
	Game::initialize(hwnd); // throws GameError

	if(!antTex.initialize(graphics,ANT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ant texture"));

	if(!hillTex.initialize(graphics,HILL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ant texture"));

	for(int i = 0 ; i < antSimNS::MAX_ANTS; i++)
	{
		ants[i].initialize(this,0,0,0,&antTex);
	}

	for(antIndex = 0 ; antIndex < antSimNS::STARTING_ANTS; antIndex++)
	{
		ants[antIndex].create(VECTOR2(GAME_WIDTH/2,GAME_HEIGHT/2));
	}

	base.initialize(this,64,64,0,&hillTex);
	base.setCenterLocation(VECTOR2(GAME_WIDTH/2,GAME_HEIGHT/2));

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void AntSim::update()
{
	for(int i = 0 ; i < antSimNS::MAX_ANTS; i++)
	{
		ants[i].update(frameTime);
	}
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void AntSim::ai()
{
}

//=============================================================================
// Handle collisions
//=============================================================================
void AntSim::collisions()
{
	

}

//=============================================================================
// Render game items
//=============================================================================
void AntSim::render()
{
	graphics->spriteBegin();                // begin drawing sprites

	for(int i = 0 ; i < antSimNS::MAX_ANTS; i++)
	{
		ants[i].draw();
	}

	base.draw();

	graphics->spriteEnd();                  // end drawing sprites	

}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void AntSim::releaseAll()
{
	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void AntSim::resetAll()
{
	Game::resetAll();
	return;
}

void AntSim::spawnAnt(VECTOR2 loc)
{
	for(int i = 0 ; i > antSimNS::MAX_ANTS; i++)
	{
		//loop index if end is reached
		if(antIndex >= antSimNS::MAX_ANTS) antIndex = 0;

		//if selected ant is unused
		if(!ants[antIndex].getActive())
		{
			ants[antIndex].create(loc);
		}

		antIndex++;
	}
}








