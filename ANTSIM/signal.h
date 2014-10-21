#pragma once
#include "game.h"

//order these by priority
enum SignalType
{
	null,
	beg, // ants may need to ask for food
	direction, //there is something interesting down this path
	queen, //the queen is alive
	colony_food, //faint food signal from colony
	food, //foods give off a scent
	ant_nearby,
};

class Signal
{
public:
	Signal(){type=SignalType::null;data=VECTOR2(-1,-1);}
	Signal(SignalType t,VECTOR2 l,Species s = BLACK){data=l;type=t;species=s;};
	SignalType getType(){return type;}
	VECTOR2 getData(){return data;}
	int getPriority(){return (int)type;}
	void setData(VECTOR2 d){data=d;}
	Species getSpecies(){return species;}
private:
	//signals tell ants about a location
	VECTOR2 data;
	SignalType type;
	Species species;
};