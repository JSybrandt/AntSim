/* 
 Group #: Group 5
 Members: Noah Cusimano, Seth Loew, Caelan Mayberry, Justin Sybrandt
 Course: COMP 322, Advanced Programming 
 Date: 30 August 2014 
 Description: This file implements a component of the 
 semester project, stage 2. 
*/ 

#pragma once
#include "Actor.h"
#include "pheromone.h"
#include "Queen.h"

class AntSim;

namespace colonyNS
{
	const float LIFE_EXPECTANCY = 10;
	const float METABOLISM = 1;
	const float STOMACH_SIZE = 1000;
	const float STARVATION_DAMAGE = 10;
	const float OLD_AGE_DAMAGE = 10;
	const float COLONY_SPEED = 0;
	const float COLONY_MAX_HEALTH = 10000;
	const float BIRTHRATE = 5;
}

class Colony: public Actor
{
private:
	std::string name;
	std::string color;
	float age;
	AntSim* world;
	Species species;
	float resetRate;
	float foodLevel;		//amount of food in the colony
	bool alive;
	Pheromone * pher;
	float spawnCooldown;
	Queen* queen;

public:
	Colony();
	~Colony();
	void update(float frameTime);
	void draw();
	void create(VECTOR2 location, Species s);
	bool initialize(AntSim *gamePtr, int width, int height, int ncols,TextureManager *textureM);
	void die();

	virtual float getFood()			const {return foodLevel;}

	virtual float getAge()			const {return age;}

	// Return name;
	virtual std::string getName()			const {return name;}

	virtual Species getSpecies()			const {return species;}

	float requestFood(float amount);
};