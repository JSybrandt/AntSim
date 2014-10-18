// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Game Engine Part 1
// Chapter 4 RedSpace.cpp v1.0
// RedSpace is the class we create.

#include "antSim.h"

using std::list;

//=============================================================================
// Constructor
//=============================================================================
AntSim::AntSim() {
	srand((unsigned)time(0)); 
	antIndex = 0;
	foodIndex = 0;
	pherIndex = 0;
	clickedLastFrame = false;
	rectWidth = float(GAME_WIDTH)/antSimNS::HOR_NUM_COL_RECTS;
	rectHeight = float(GAME_HEIGHT)/antSimNS::HOR_NUM_COL_RECTS;
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

	if(base.getSpawn()) {
		VECTOR2 test(base.getCenterX(),base.getCenterY());
		spawnAnt(test);
	}
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
	
	for(int i = 0 ; i  < antSimNS::HOR_NUM_COL_RECTS;  i++)
		for(int j = 0 ; j  < antSimNS::HOR_NUM_COL_RECTS;  j++)
			colRects[i][j].checkCollisions();

	//lopp ants
	for(int j = 0; j < antSimNS::MAX_ANTS; j++)
	{
		if(input->getMouseRButton() && mouse.collidesWith(ants[j],collision)) {
			mouse.getInfo(ants[j]);
		}
		if(input->getMouseRButton() && mouse.collidesWith(base,collision)) {
			mouse.getInfo(base);
		}
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

void AntSim::spawnAnt(VECTOR2 loc)
{
	for(int i = 0 ; i < antSimNS::MAX_ANTS; i++)
	{
		//loop index if end is reached
		if(antIndex >= antSimNS::MAX_ANTS) antIndex = 0;

		//if selected ant is unused
		if(!ants[antIndex].getActive())
		{
			ants[antIndex].create(loc);
			break;
		}

		antIndex++;
	}
}

void AntSim::spawnFood(VECTOR2 loc)
{
	for(int i = 0 ; i < antSimNS::MAX_FOOD; i++)
	{
		//loop index if end is reached
		if(foodIndex >= antSimNS::MAX_FOOD) foodIndex = 0;

		//if selected ant is unused
		if(!food[foodIndex].getActive())
		{
			food[foodIndex].create(loc);
			Signal s(SignalType::food,loc);
			spawnPher(loc,s);
			placeObjectInProperRect(&food[foodIndex]);
			break;
		}

		foodIndex++;
	}
}

void AntSim::spawnPher(VECTOR2 loc, Signal s)
{
	for(int i = 0 ; i < antSimNS::MAX_PHEROMONE; i++)
	{
		//loop index if end is reached
		if(pherIndex >= antSimNS::MAX_PHEROMONE) pherIndex = 0;

		//if selected ant is unused
		if(!pheromones[pherIndex].getActive())
		{
			pheromones[pherIndex].create(loc,s);
			placeObjectInProperRect(&pheromones[pherIndex]);
			break;
		}

		pherIndex++;
	}
}

AntSim::collisionRect::collisionRect()
{
	ants.clear();
	objects.clear();

}

void AntSim::collisionRect::addActor(Ant* in)
{
	ants.push_front(in);
}

void AntSim::collisionRect::addActor(Actor* in)
{
	objects.push_front(in);
}


void AntSim::collisionRect::checkCollisions()
{
	VECTOR2 coll;
	for(Ant* ant : ants){
		for(list<Actor*>::iterator obj = objects.begin(); obj != objects.end(); obj++){
			
			if((*obj)->getActive()){
				if(ant->collidesWith(**obj,coll)){
					ant->touches(*obj);
				}
			}
			else{
				auto old = obj;
				obj++;
				objects.erase(old);
				if(obj == objects.end()) break;
			}
		}

		for(Ant* ant2 : ants){
			if(ant != ant2 && ant->collidesWith(*ant2,coll)){
				ant->touches(ant2);
				ant2->touches(ant);
			}
		}
	}
	ants.clear();
}

void AntSim::placeObjectInProperRect(Actor* in)
{
	bool isAnt = dynamic_cast<Ant*>(in);

	int lx = in->getX()/rectWidth;
	int ly = in->getY()/rectHeight;
	int ux = (in->getX()+in->getWidth())/rectWidth;
	int uy = (in->getY()+in->getHeight())/rectHeight;

	for(int i = lx; i <= ux; i++)
	{
		for(int j = ly; j < uy; j++)
		{
			if(isAnt)
				colRects[i][j].addActor(static_cast<Ant*>(in));	
			else 
				colRects[i][j].addActor(in);	
		}
	}

}






