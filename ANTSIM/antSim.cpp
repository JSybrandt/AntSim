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
AntSim::AntSim() {
	srand((unsigned)time(0)); 
	antIndex = 0;
	foodIndex = 0;
	pherIndex = 0;
	clickedLastFrame = false;
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

	if(!foodTex.initialize(graphics,FOOD_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing food texture"));

	if(!pherTex.initialize(graphics,PHEROMONE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pheromone texture"));

	for(int i = 0 ; i < antSimNS::MAX_ANTS; i++)
	{
		ants[i].initialize(this,0,0,0,&antTex);
	}

	for(int i = 0 ; i < antSimNS::MAX_FOOD; i++)
	{
		food[i].initialize(this,0,0,0,&foodTex);
	}

	for(int i = 0 ; i < antSimNS::MAX_PHEROMONE; i++)
	{
		pheromones[i].initialize(this,0,0,0,&pherTex);
	}

	for(antIndex = 0 ; antIndex < antSimNS::STARTING_ANTS; antIndex++)
	{
		ants[antIndex].create(VECTOR2(GAME_WIDTH/2,GAME_HEIGHT/2));
	}

	base.initialize(this,64,64,0,&hillTex);
	base.setCenterLocation(VECTOR2(GAME_WIDTH/2,GAME_HEIGHT/2));
	mouse.initialize(this,input,graphics, 0,0,0);



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

	for(int i = 0 ; i < antSimNS::MAX_FOOD; i++)
	{
		food[i].update(frameTime);
	}

	for(int i = 0 ; i < antSimNS::MAX_PHEROMONE; i++)
	{
		pheromones[i].update(frameTime);
	}

	if(input->getMouseLButton())
	{
		if(!clickedLastFrame)
		{
			VECTOR2 mouseLoc(input->getMouseX(),input->getMouseY());
			spawnFood(mouseLoc);
		}
		clickedLastFrame = true;
	}
	else clickedLastFrame = false;


	base.update(frameTime);
	mouse.update(frameTime);
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
	VECTOR2 collision;
	
	//lopp ants
	for(int j = 0; j < antSimNS::MAX_ANTS; j++)
	{

		//check ants with pheromone
		for(int i = 0 ; i < antSimNS::MAX_PHEROMONE; i++)
		{
			//if an ant is in range of the pheromone
			if(pheromones[i].collidesWith(ants[j],collision))
			{

				ants[j].receiveSignal(pheromones[i].getSignal());
			}
		}

		//check ant with food
		for(int i = 0 ; i < antSimNS::MAX_FOOD; i++)
		{
			//if an ant is in range of the pheromone
			if(ants[i].collidesWith(food[j],collision))
			{
				ants[i].touches(&food[j]);
			}
		}

		for(int i = 0; i < antSimNS::MAX_ANTS; i++)
		{
			if(ants[i].collidesWith(ants[j],collision))
			{
				ants[i].touches(&ants[j]);
				ants[j].touches(&ants[i]);
			}
		}


	}
	for(int i = 0; i < antSimNS::MAX_ANTS; i++) {
		if(input->getMouseRButton() && mouse.collidesWith(ants[i],collision)) {
			mouse.getInfo(ants[i]);
		}
	}
	if(input->getMouseRButton() && mouse.collidesWith(base,collision)) {
			mouse.getInfo(base);
	}

}

//=============================================================================
// Render game items
//=============================================================================
void AntSim::render()
{
	graphics->spriteBegin();                // begin drawing sprites

	base.draw();

	for(int i = 0 ; i < antSimNS::MAX_PHEROMONE; i++)
	{
		pheromones[i].draw();
	}

	for(int i = 0 ; i < antSimNS::MAX_ANTS; i++)
	{
		ants[i].draw();
	}

	for(int i = 0 ; i < antSimNS::MAX_FOOD; i++)
	{
		food[i].draw();
	}

	if(input->getMouseRButton()) {
		mouse.print();
	}


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

Ant* AntSim::spawnAnt(VECTOR2 loc)
{
	Ant* result = nullptr;
	for(int i = 0 ; i < antSimNS::MAX_ANTS; i++)
	{
		//loop index if end is reached
		if(antIndex >= antSimNS::MAX_ANTS) antIndex = 0;

		//if selected ant is unused
		if(!ants[antIndex].getActive())
		{
			ants[antIndex].create(loc);
			result = &ants[antIndex];
			break;
		}
		antIndex++;
	}
	return result;
}

Food* AntSim::spawnFood(VECTOR2 loc)
{
	Food* result = nullptr;
	for(int i = 0 ; i < antSimNS::MAX_FOOD; i++)
	{
		//loop index if end is reached
		if(foodIndex >= antSimNS::MAX_FOOD) foodIndex = 0;

		//if selected ant is unused
		if(!food[foodIndex].getActive())
		{
			food[foodIndex].create(this,loc);
			result = &food[foodIndex];
			break;
		}

		foodIndex++;
	}
	return result;
}

Pheromone* AntSim::spawnPher(VECTOR2 loc, Signal s)
{
	Pheromone * result = nullptr;
	for(int i = 0 ; i < antSimNS::MAX_PHEROMONE; i++)
	{
		//loop index if end is reached
		if(pherIndex >= antSimNS::MAX_PHEROMONE) pherIndex = 0;

		//if selected ant is unused
		if(!pheromones[pherIndex].getActive())
		{
			pheromones[pherIndex].create(loc,s);
			result = &pheromones[pherIndex];
			break;
		}

		pherIndex++;
	}
	return result;
}










