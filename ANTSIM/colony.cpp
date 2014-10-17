#include "Colony.h"

Colony::Colony():Actor()
{
	age = 0;
	resetRate = .05;
	foodLevel = colonyNS::STOMACH_SIZE;
	alive = true;
	spawn = false;
	setActive(true);
	setScale(5);
}

Colony::~Colony()
{
}

void Colony::update(float frameTime)
{
	if(getActive())
	{
		//age
		age += frameTime;
		//if(age > colonyNS::LIFE_EXPECTANCY) health -= colonyNS::OLD_AGE_DAMAGE * frameTime;


		//consume food
		//foodLevel -= colonyNS::METABOLISM*frameTime;
		//if(foodLevel < 0) health -= colonyNS::STARVATION_DAMAGE * frameTime;

		//Health, die.
		if(health <= 0) die();

		if(birthRate > 0)
		{
			spawn = false;
			birthRate -= frameTime;
		}
		if(birthRate < 0) { 
			birthRate = resetRate;
			spawn = true;
		}

	}

}

void Colony::draw()
{
	if(getActive()) Actor::draw();
}

void Colony::create(VECTOR2 location)
{
	setCenterLocation(location);
	age = 0;
	setActive(true);
	foodLevel = colonyNS::STOMACH_SIZE;
	alive = true;
	health = colonyNS::COLONY_MAX_HEALTH * (rand()%100/100)*25+75;
}

bool Colony::initialize(AntSim *gamePtr, int width, int height, int ncols,TextureManager *textureM)
{
	world = gamePtr;
	return Actor::initialize((Game*)gamePtr,width,height,ncols,textureM);
}

void Colony::die()
{
	//TODO:leave dead bodies, use animation
	alive = false;
	setActive(false);
}