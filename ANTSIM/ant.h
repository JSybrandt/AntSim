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
#include "signal.h"
#include "food.h"
#include "pheromone.h"

class AntSim;

namespace antNS
{
	const float QUEEN_LIFE_EXPECTANCY = 30000;
	const float LIFE_EXPECTANCY = 10;
	const float YOUNG_AGE = LIFE_EXPECTANCY * 0.6;//NEC - ants are young when 1%-60% of life expectancy
	const float MIDDLE_AGE = LIFE_EXPECTANCY * 0.9;//NEC - ants are middle aged when 60%-90% of life expectancy
	const float OLD_AGE = LIFE_EXPECTANCY;//NEC - ants are old when 90%-100% of life expectancy
	const float METABOLISM = 2;//NEC - Changed from 20 to 2 for testing
	const float STOMACH_SIZE = 100;
	const float QUEEN_STOMACH_SIZE = 200;
	const float STARVATION_DAMAGE = 10;
	const float OLD_AGE_DAMAGE = 1;//NEC - Changed from 10 to 1 for testing
	const float ANT_SPEED = 50;
	const float ANT_MAX_HEALTH = 100;
	const float QUEEN_MAX_HEALTH = 200;
	const int NUM_SIMULTANEOUS_SIGNALS = 10;

	const float ATTACK_COOLDOWN = 0.25;
	const float ATTACK_MIN_DAMAGE = 3;
	const float ATTACK_DAMAGE_RANGE = 7;

}

enum Behavior{
	DEFAULT,
	EATING,
	BEGGING
};



class Ant: public Actor
{
protected:
	COLOR_ARGB color;
	float age;
	AntSim* world;
	bool isUnderground;
	bool isMale;
	float direction;
	float foodLevel;
	bool alive; //becaue we might want corpses later
	Signal signals[antNS::NUM_SIMULTANEOUS_SIGNALS];
	int signalIndex;
	Behavior behavior;
	Behavior lastFrame;
	Species species;

	float distSqrdFromQueen;

	float cooldown;

	//different versions of update based on behavior
	void youngDefaultAction(float frameTime);//NEC - young ants will wander in search of food in small radius of nest
	void middleDefaultAction(float frameTime);//NEC - middle ants will patrol medium radius of nest
	void oldDefaultAction(float frameTime);//NEC - old ants will wander in search of food in large radius of nest
	
	void hungryAction(float frameTime);

	Pheromone* pher;

	//moves ant toward given location
	void moveInDirection(VECTOR2 dir, float frameTime);

	void youngWanderAimlessly(float frameTime);//NEC - this hungry action will be called by youngDefaultAction
	void middleWanderAimlessly(float frameTime);//NEC - this hungry action will be called by middleDefaultAction
	void oldWanderAimlessly(float frameTime);//NEC - this hungry action will be called by oldDefaultAction

public:
	Ant();
	~Ant();
	void update(float frameTime);
	void draw();
	void create(VECTOR2 location, Species s = BLACK);
	bool initialize(AntSim *gamePtr, int width, int height, int ncols,TextureManager *textureM);
	void die();
	void receiveSignal(Signal s);
	virtual void touches(Actor* other);

	//called by hungry ants
	//returns the amount of food taken
	float receiveFood(float avalible);

	Behavior getBehavior(){return behavior;}

	// Return food level;
	virtual float getFood()			const {return foodLevel;}

	// Return age;
	virtual float getAge()			const {return age;}
	
	// Return name;
	virtual std::string getName()			const {return name;}

	// Return Species;
	virtual Species getSpecies()			const {return species;}

};