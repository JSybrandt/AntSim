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

	const float COOLDOWN = 10;
}

enum Behavior{
	DEFAULT,
	EATING,
	BEGGING
};



class Ant: public Actor
{
private:
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

	float cooldown;

	//different versions of update based on behavior
	void defaultAction(float frameTime);
	void hungryAction(float frameTime);

	Pheromone* pher;

	//moves ant toward given location
	void moveInDirection(VECTOR2 dir, float frameTime);

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
};