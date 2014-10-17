#pragma once
#include "actor.h"
#include "signal.h"
#include "graphics.h"

namespace pheromoneNS{
	const float FOOD_RADIUS = 100;
	const COLOR_ARGB FOOD_COLOR = graphicsNS::GREEN;
	const float FOOD_LIFESPAN = 10;


	const float BEG_RADIUS = 30;
	const COLOR_ARGB BEG_COLOR = graphicsNS::LTGRAY;
	const float BEG_LIFESPAN = 5;

	
	const float DEFAULT_RADIUS = 80;
	const COLOR_ARGB DEFAULT_COLOR = graphicsNS::WHITE;
	const float DEFAULT_LIFESPAN = 5;

	const float DISSIPATION_RATE = 7;
};

class Pheromone: public Actor
{
public:
	Pheromone();
	~Pheromone();
	void create(VECTOR2 loc, Signal s);
	void update(float frameTime);
	void draw();//draw will include a color based on the type
	Signal getSignal(){return signal;}
private:
	Signal signal;
	float age;
	float lifeSpan;
	COLOR_ARGB color;
	VECTOR2 trueCenter;
};