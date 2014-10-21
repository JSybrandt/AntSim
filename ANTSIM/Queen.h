#pragma once
#include "ant.h"
#include "Actor.h"
#include "signal.h"
#include "food.h"

class Queen:public Ant{

private:
	float age;
	AntSim* world;
	bool isUnderground;
	float foodLevel;
	bool alive; //becaue we might want corpses later
	Signal signals[antNS::NUM_SIMULTANEOUS_SIGNALS];
	int signalIndex;
	Behavior behavior;
	Species species;

	float cooldown;

	//different versions of update based on behavior
	void defaultAction(float frameTime);
	void hungryAction(float frameTime);


public:
	Queen();
	~Queen();
	void draw();
	void update(float frameTime);
	void Reproduce(VECTOR2 location,Species spc);
	void create_Ant(VECTOR2 location);
	void create(VECTOR2 location,Species spc);
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

	// Return species;
	virtual Species getSpecies()			const {return species;}

};