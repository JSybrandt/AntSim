#include "pheromone.h"

Pheromone::Pheromone()
{
	setActive(false);
}
Pheromone::~Pheromone(){}
void Pheromone::create(VECTOR2 loc, Signal s, float life,float radius)
{
	setScale(radius*2/getWidth());
	setCenterLocation(loc);
	signal=s;
	lifeSpan = life;
	setActive(true);
}

void Pheromone::create(VECTOR2 loc, Signal s)
{
	//TODO: get life and rad from type
	create(loc,s,50,50);
}

void Pheromone::update(float frameTime)
{
	if(getActive())
	{
		age += frameTime;
		if(age > lifeSpan) setActive(false);
	}
}

void Pheromone::draw()
{
	if(getActive())
	{
		//TODO: color by signal type
		Actor::draw();
	}
}