#include "food.h"

Food::Food()
{
	value = foodNS::DEFAULT_FOOD_VAL;
	setActive(false);
}

Food::~Food(){};

void Food::create(VECTOR2 loc)
{
	setActive(true);
	setCenterLocation(loc);
	
}