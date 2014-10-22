#include "pheromone.h"

using namespace pheromoneNS;

Pheromone::Pheromone()
{
	setActive(false);
	setX(0); setY(0);
}
Pheromone::~Pheromone(){}

void Pheromone::create(VECTOR2 loc, Signal s)
{
	
	//setting radius is a bad idea, set scale instead
	switch (s.getType())
	{
	case SignalType::food:
		color = FOOD_COLOR;
		startingRadius = FOOD_RADIUS;
		lifeSpan = FOOD_LIFESPAN;
		break;
	case SignalType::beg:
		color = BEG_COLOR;
		startingRadius = BEG_RADIUS;
		lifeSpan = BEG_LIFESPAN;
		break;
	case SignalType::colony_food:
		color = COLONY_FOOD_COLOR;
		startingRadius = COLONY_FOOD_RADIUS;
		lifeSpan = COLONY_FOOD_LIFESPAN;
		break;
	case SignalType::ant_nearby:
		color = ANT_NEARBY_COLOR;
		startingRadius = ANT_NEARBY_RADIUS;
		lifeSpan = ANT_NEARBY_LIFESPAN;
		break;
	case SignalType::queen:
		color = QUEEN_COLOR;
		startingRadius = QUEEN_RADIUS;
		lifeSpan = QUEEN_LIFESPAN;
		break;
	default:
		color = DEFAULT_COLOR;
		startingRadius = DEFAULT_RADIUS;
		lifeSpan = DEFAULT_LIFESPAN;
		break;
	}

	drawnRadius = startingRadius;

	setScale(1);
	rawRadius = getWidth()/2;

	setSize(drawnRadius);

	setCenterLocation(loc);
	trueCenter = loc;
	signal=s;
	setActive(true);
	age = 0;
	

}

void Pheromone::update(float frameTime)
{
	if(getActive())
	{
		age += frameTime;
		if(age > lifeSpan) setActive(false);

		drawnRadius-=pheromoneNS::DISSIPATION_RATE*frameTime;

		if(drawnRadius <= pheromoneNS::MIN_RADIUS){
			setActive(false);
		}
		else{
			setSize(drawnRadius);
			setCenterLocation(trueCenter);
		}

	}
}

void Pheromone::draw()
{
	if(getActive())
	{
		Actor::draw(color);
	}
}

void Pheromone::refresh()
{
	age = 0;
	drawnRadius = startingRadius;
}

void Pheromone::setSize(float delR)
{
	//its better if no one touches this, it works because collision radius is dependent of scale
	setScale(delR/rawRadius);
	setCenterLocation(trueCenter);
}

void Pheromone::setCenterLocation(VECTOR2 newLoc)
{
	Actor::setCenterLocation(newLoc);
	trueCenter = newLoc;
}