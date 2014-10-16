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

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void AntSim::update()
{

}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void AntSim::ai()
{}

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









