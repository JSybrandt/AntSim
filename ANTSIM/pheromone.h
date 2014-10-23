#pragma once
#include "actor.h"
#include "signal.h"
#include "graphics.h"

namespace pheromoneNS{
	
	const float FOOD_RADIUS = 100;
	const COLOR_ARGB FOOD_COLOR = graphicsNS::GREEN;
	const float FOOD_LIFESPAN = 10;

	const float COLONY_FOOD_RADIUS = 300;
	const COLOR_ARGB COLONY_FOOD_COLOR = graphicsNS::ALPHA50;
	const float COLONY_FOOD_LIFESPAN = 10;

	const float BEG_RADIUS = 30;
	const COLOR_ARGB BEG_COLOR = graphicsNS::LTGRAY;
	const float BEG_LIFESPAN = 5;

	const float ANT_NEARBY_RADIUS = 50;
	const COLOR_ARGB ANT_NEARBY_COLOR = graphicsNS::BLUE;
	const float ANT_NEARBY_LIFESPAN = 10;

	const float QUEEN_RADIUS = 100000;//NEC
	const COLOR_ARGB QUEEN_COLOR = graphicsNS::BLACK;
	const float QUEEN_LIFESPAN = 25;
	
	const float DEFAULT_RADIUS = 80;
	const COLOR_ARGB DEFAULT_COLOR = graphicsNS::WHITE;
	const float DEFAULT_LIFESPAN = 5;


	const float DISSIPATION_RATE = 50;
	const float MIN_RADIUS = 0;
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
	void setSignal(Signal s){signal =s;}
	void refresh();

	//does not update data
	void setCenterLocation(VECTOR2 newPos);
	
	void setSize(float desiredRad);

private:

	Signal signal;
	float age;
	float lifeSpan;
	COLOR_ARGB color;
	VECTOR2 trueCenter;
	float startingRadius;
	float drawnRadius;
	float rawRadius;

};