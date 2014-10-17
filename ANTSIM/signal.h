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
	Signal(){type=SignalType::null;}
	Signal(SignalType t,VECTOR2 l){data=l;type=t;};
private:
	//signals tell ants about a location
	VECTOR2 data;
	SignalType type;
};