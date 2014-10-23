#pragma once
#include "Actor.h"
#include "signal.h"
#include "food.h"
#include "pheromone.h"
#include "ant.h"

namespace queenNS{
	const float BIRTH_RATE = 1;
}

class Queen:public Ant{


	//different versions of update based on behavior
	void defaultAction(float frameTime);
	void hungryAction(float frameTime);


public:
	Queen();
	~Queen();
	void update(float frameTime);
	void Reproduce(VECTOR2 location,Species spc);
	void create(VECTOR2 location,Species spc);
	bool initialize(AntSim *gamePtr, int width, int height, int ncols,TextureManager *textureM);

};