#pragma once
#include "Actor.h"
#include "signal.h"
class AntSim;

namespace antNS
{
	const float LIFE_EXPECTANCY = 10;
	const float METABOLISM = 1;
	const float STOMACH_SIZE = 100;
	const float STARVATION_DAMAGE = 10;
	const float OLD_AGE_DAMAGE = 10;
	const float ANT_SPEED = 50;
	const float ANT_MAX_HEALTH = 100;
}

class Ant: public Actor
{
private:
	float age;
	AntSim* world;
	bool isUnderground;
	bool isMale;
	float direction;
	float foodLevel;
	bool alive;
public:
	Ant();
	~Ant();
	void update(float frameTime);
	void draw();
	void create(VECTOR2 location);
	bool initialize(AntSim *gamePtr, int width, int height, int ncols,TextureManager *textureM);
	void die();
	void receiveSignal(Signal s);
};