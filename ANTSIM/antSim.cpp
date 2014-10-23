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

	if(!debugText.initialize(graphics,10,false,false,"Consolas"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing debug text"));

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

	blackBase.initialize(this,64,64,0,&hillTex);
	blackBase.create(VECTOR2(GAME_WIDTH/4,GAME_HEIGHT/4), BLACK);

	redBase.initialize(this,64,64,0,&hillTex);
	redBase.create(VECTOR2(3*GAME_WIDTH/4,3*GAME_HEIGHT/4), RED);

	mouse.initialize(this, graphics, 0,0,0, &pherTex);

	blackQueen.initialize(this,0,0,0,&antTex);
	redQueen.initialize(this,0,0,0,&antTex);

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
		if(ants[i].getActive())placeAntObjectInProperRect(&ants[i]);
	}

	for(int i = 0 ; i < antSimNS::MAX_FOOD; i++)
	{
		food[i].update(frameTime);
		if(food[i].getActive())placeObjectInProperRect(&food[i]);
	}

	for(int i = 0 ; i < antSimNS::MAX_PHEROMONE; i++)
	{
		pheromones[i].update(frameTime);
		if(pheromones[i].getActive())placeObjectInProperRect(&pheromones[i]);
	}

	if(blackQueen.getActive())
	{
		blackQueen.update(frameTime);
		placeAntObjectInProperRect(&blackQueen);
	}

	if(redQueen.getActive())
	{
		redQueen.update(frameTime);
		placeAntObjectInProperRect(&redQueen);
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

	blackBase.update(frameTime);
	redBase.update(frameTime);

	placeObjectInProperRect(&blackBase);
	placeObjectInProperRect(&redBase);

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
		for(int j = 0 ; j  < antSimNS::HOR_NUM_COL_RECTS;  j++) {
			colRects[i][j].checkCollisions();
			colRects[i][j].clear();
		}

	//Mouse collision
	bool found = false;
	if(input->getMouseRButton()) {
		for(int i = 0; i < antSimNS::MAX_ANTS; i++) {
			if(mouse.collidesWith(ants[i],collision)) {
				mouse.getInfo(ants[i]);
				found = true;
				break;
			}
		}
		if(!found && mouse.collidesWith(blackBase,collision)) {
			mouse.getInfo(blackBase);
			found = true;
		}
		else if(!found && mouse.collidesWith(redBase,collision)) {
			found = true;
			mouse.getInfo(redBase);
		}
	}

	//End Function
}

//=============================================================================
// Render game items
//=============================================================================
void AntSim::render()
{
	graphics->spriteBegin();                // begin drawing sprites

	blackBase.draw();
	redBase.draw();

	for(int i = 0 ; i < antSimNS::MAX_FOOD; i++)
	{
		food[i].draw();
	}

	for(int i = 0 ; i < antSimNS::MAX_PHEROMONE; i++)
	{
		pheromones[i].draw();
	}

	for(int i = 0 ; i < antSimNS::MAX_ANTS; i++)
	{
		ants[i].draw();
	}


	if(input->getMouseRButton()) {
		mouse.print();
		mouse.draw();
	}

	blackQueen.draw();
	redQueen.draw();

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

//=============================================================================
// Spawning Functions
//=============================================================================
Ant* AntSim::spawnAnt(VECTOR2 loc, Species spc)
{
	Ant* result = nullptr;
	for(int i = 0 ; i < antSimNS::MAX_ANTS; i++)
	{
		//loop index if end is reached
		if(antIndex >= antSimNS::MAX_ANTS) antIndex = 0;

		//if selected ant is unused
		if(!ants[antIndex].getActive())
		{
			ants[antIndex].create(loc, spc);
			result = &ants[antIndex];
			placeAntObjectInProperRect(&ants[antIndex]);
			break;
		}
		antIndex++;
	}
	return result;
}

Queen* AntSim::spawnQueen(VECTOR2 loc, Species spc)
{
	Queen* result = nullptr;
	if(spc==BLACK)
	{
		blackQueen.create(loc,spc);
		result = &blackQueen;
	}
	else if(spc==RED)
	{
		redQueen.create(loc,spc);
		result = &redQueen;
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
			placeObjectInProperRect(&food[foodIndex]);
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
			placeObjectInProperRect(&pheromones[pherIndex]);
			break;
		}

		pherIndex++;
	}
	return result;
}

AntSim::collisionRect::collisionRect()
{
	ants.clear();
	objects.clear();

}

void AntSim::collisionRect::clear() {
	ants.clear();
	objects.clear();
}

void AntSim::collisionRect::addAnt(Ant* in)
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
}

void AntSim::placeObjectInProperRect(Actor* in)
{
	//bool isAnt = dynamic_cast<Ant*>(in);

	int lx = max(in->getX()/rectWidth,0);
	int ly = max(in->getY()/rectHeight,0);
	int ux = min((in->getX()+in->getWidth())/rectWidth,antSimNS::HOR_NUM_COL_RECTS-1);
	int uy = min((in->getY()+in->getHeight())/rectHeight,antSimNS::HOR_NUM_COL_RECTS-1);


	for(int i = lx; i <= ux; i++) {
		for(int j = ly; j <= uy; j++) {
			colRects[i][j].addActor(in);	
		}
	}

}

void AntSim::placeAntObjectInProperRect(Ant* in)
{

	int lx = max(in->getX()/rectWidth,0);
	int ly = max(in->getY()/rectHeight,0);
	int ux = min((in->getX()+in->getWidth())/rectWidth,antSimNS::HOR_NUM_COL_RECTS-1);
	int uy = min((in->getY()+in->getHeight())/rectHeight,antSimNS::HOR_NUM_COL_RECTS-1);

	for(int i = lx; i <= ux; i++) {
		for(int j = ly; j <= uy; j++) {
			colRects[i][j].addAnt(in);	
		}
	}

}





