#pragma once
#include "actor.h"
#include "signal.h"

namespace pheromoneNS{
	
};

class Pheromone: public Actor
{
public:
	Pheromone();
	~Pheromone();
	void create(VECTOR2 loc, Signal s);
	void create(VECTOR2 loc, Signal s, float life, float radius);
	void update(float frameTime);
	void draw();//draw will include a color based on the type
	Signal getSignal(){return signal;}
private:
	Signal signal;
	float age;
	float lifeSpan;
};