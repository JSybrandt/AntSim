#pragma once

#include"Actor.h"

namespace foodNS{
	const float DEFAULT_FOOD_VAL = 10;
	const float LIFE_SPAN = 10;
}

//TODO: food should probably give off a chemical signal in order to inform ants that the food is near. 

class Food : public Actor
{
private:
	float value;
	float age;
public:
	Food();
	~Food();

	void create(VECTOR2 loc);

	void update(float frameTime);

	//ants call this, request certain amount of food, are given the result;
	float eat(float requested);
};