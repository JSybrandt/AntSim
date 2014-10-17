#pragma once
#include "game.h"
enum SignalType
{
	null,
	food, //foods give off a scent
	beg, // ants may need to ask for food
	direction, //there is something interesting down this path
	queen //the queen is alive
};

class Signal
{
public:
	Signal(){type=SignalType::null;data=VECTOR2(-1,-1);priority=-1;}
	Signal(SignalType t,VECTOR2 l, float p=1){data=l;type=t;priority = p;};
	SignalType getType(){return type;}
	VECTOR2 getData(){return data;}
	float getPriority(){return priority;};
private:
	//signals tell ants about a location
	VECTOR2 data;
	SignalType type;
	float priority;
};