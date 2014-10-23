/* 
 Group #: Group 5
 Members: Noah Cusimano, Seth Loew, Caelan Mayberry, Justin Sybrandt
 Course: COMP 322, Advanced Programming 
 Date: 30 August 2014 
 Description: This file implements a component of the 
 semester project, stage 2. 
*/ 

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

	//void setLocation(D3DXVECTOR2 loc) {location.setData(loc);}
	//D3DXVECTOR2 getLocation() {return location.getData();}

};