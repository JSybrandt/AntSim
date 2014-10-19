#include "food.h"
#include "antSim.h"

Food::Food()
{
	value = foodNS::DEFAULT_FOOD_VAL;
	setActive(false);
	age = 0;
}

Food::~Food(){};

void Food::create(AntSim * w, VECTOR2 loc)
{
	setActive(true);
	setCenterLocation(loc);
	age = 0;
	//spawn a pher to point to the current food
	pher = w->spawnPher(loc,Signal(SignalType::food,loc));
}

float Food::eat(float req)
{
	req = min(value,req);
	value -= req;
	if(value<= 0)setActive(false);
	return req;
}

void Food::update(float frameTime)
{
	if(getActive())
	{
		pher->refresh();
		age += frameTime;
		if(age >= foodNS::LIFE_SPAN) setActive(false);
		
	}
}