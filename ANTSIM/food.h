#pragma once

#include"Actor.h"

namespace foodNS{
	const float DEFAULT_FOOD_VAL = 10;
}

//TODO: food should probably give off a chemical signal in order to inform ants that the food is near. 

class Food : public Actor
{
private:
	float value;
public:
	Food();
	~Food();

	void create(VECTOR2 loc);
};