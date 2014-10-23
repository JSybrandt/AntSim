#pragma once
#include "Actor.h"
#include "signal.h"
#include "food.h"
#include "pheromone.h"
#include "ant.h"

class Queen:public Ant{

private:
	float age;
	AntSim* world;
	bool isUnderground;
	float foodLevel;
	bool alive; //becaue we might want corpses later
	Signal signals[antNS::NUM_SIMULTANEOUS_SIGNALS];
	//Signal location;
	int signalIndex;
	Behavior behavior;
	Species species;

	Signal location;

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

	void setLocation(D3DXVECTOR2 loc) {location.setData(loc);}
	D3DXVECTOR2 getLocation() {return location.getData();}

};