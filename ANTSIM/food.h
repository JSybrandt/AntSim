/* 
 Group #: Group 5
 Members: Noah Cusimano, Seth Loew, Caelan Mayberry, Justin Sybrandt
 Course: COMP 322, Advanced Programming 
 Date: 30 August 2014 
 Description: This file implements a component of the 
 semester project, stage 2. 
*/ 

#pragma once

#include"Actor.h"

#include"Pheromone.h"

#include"signal.h"

class AntSim;

namespace foodNS{
	const float DEFAULT_FOOD_VAL = 100;
	const float LIFE_SPAN = 10;
}

//TODO: food should probably give off a chemical signal in order to inform ants that the food is near. 

class Food : public Actor
{
private:
	float value;
	float age;
	Pheromone * pher;
public:
	Food();
	~Food();

	void create(AntSim * w, VECTOR2 loc);

	void update(float frameTime);

	//ants call this, request certain amount of food, are given the result;
	float eat(float requested);
};