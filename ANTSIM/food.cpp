/* 
 Group #: Group 5
 Members: Noah Cusimano, Seth Loew, Caelan Mayberry, Justin Sybrandt
 Course: COMP 322, Advanced Programming 
 Date: 30 August 2014 
 Description: This file implements a component of the 
 semester project, stage 2. 
*/ 

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
	value = foodNS::DEFAULT_FOOD_VAL;
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
		if(pher != nullptr)pher->refresh();
		age += frameTime;
		if(age >= foodNS::LIFE_SPAN || value <= 0) setActive(false);
		
	}
}