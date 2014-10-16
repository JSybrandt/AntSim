#pragma once
#include "Actor.h"

class AntSim;

namespace colonyNS
{
	const float LIFE_EXPECTANCY = 10;
	const float METABOLISM = 1;
	const float STOMACH_SIZE = 100;
	const float STARVATION_DAMAGE = 10;
	const float OLD_AGE_DAMAGE = 10;
	const float COLONY_SPEED = 50;
	const float COLONY_MAX_HEALTH = 100;
}

class Colony: public Actor
{
private:
	float age;
	AntSim* world;
	float foodLevel;		//amount of food in the colony
	bool alive;
public:
	Colony();
	~Colony();
	void update(float frameTime);
	void draw();
	void create(VECTOR2 location);
	bool initialize(AntSim *gamePtr, int width, int height, int ncols,TextureManager *textureM);
	void die();
};