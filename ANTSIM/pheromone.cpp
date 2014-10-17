#include "pheromone.h"

using namespace pheromoneNS;

Pheromone::Pheromone()
{
	setActive(false);
}
Pheromone::~Pheromone(){}

void Pheromone::create(VECTOR2 loc, Signal s)
{
	setScale(radius*2/getWidth());
	this->radius = radius;
	setCenterLocation(loc);
	trueCenter = loc;
	signal=s;
	setActive(true);
	age = 0;



	switch (s.getType())
	{
	case SignalType::food:
		color = FOOD_COLOR;
		radius = FOOD_RADIUS;
		lifeSpan = FOOD_LIFESPAN;
		break;
	case SignalType::beg:
		color = BEG_COLOR;
		radius = BEG_RADIUS;
		lifeSpan = BEG_LIFESPAN;
		break;
	default:
		color = DEFAULT_COLOR;
		radius = DEFAULT_RADIUS;
		lifeSpan = DEFAULT_LIFESPAN;
		break;
	}

}

void Pheromone::update(float frameTime)
{
	if(getActive())
	{
		age += frameTime;
		if(age > lifeSpan) setActive(false);

		//makes circle shrink
		radius -= pheromoneNS::DISSIPATION_RATE * frameTime;
		setScale(1);
		setScale(radius*2/getWidth());
		setCenterLocation(trueCenter);

	}
}

void Pheromone::draw()
{
	if(getActive())
	{
		Actor::draw(color);
	}
}