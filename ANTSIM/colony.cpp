#include "Colony.h"

#include "antSim.h"

Colony::Colony():Actor()
{
	age = 0;
	resetRate = 5;
	foodLevel = colonyNS::STOMACH_SIZE;
	alive = false;
	spawnCooldown = 0;
	setActive(false);
	//radius = .01;
	setScale(1);
	name = "Colony";
	pher = nullptr;
}

Colony::~Colony()
{
}

void Colony::update(float frameTime)
{
	if(getActive())
	{
		//age
		age += frameTime;
		//if(age > colonyNS::LIFE_EXPECTANCY) health -= colonyNS::OLD_AGE_DAMAGE * frameTime;

		if(pher == nullptr)
		{
			//the base has a low priority food signal
			pher = world->spawnPher(*getCenter(),Signal(SignalType::colony_food,*getCenter()));
		}
		else
		{
			pher->refresh();
		}

		//Health, die.
		if(health <= 0) die();

		spawnCooldown -= frameTime;

		if(spawnCooldown <= 0)
		{
			world->spawnAnt(*getCenter());
			spawnCooldown += colonyNS::BIRTHRATE;
		}
		

	}

}

void Colony::draw()
{
	if(getActive()) Actor::draw();
}

void Colony::create(VECTOR2 location, Species s)
{
	setCenterLocation(location);
	age = 0;
	species = s;
	setActive(true);
	foodLevel = colonyNS::STOMACH_SIZE;
	alive = true;
	health = colonyNS::COLONY_MAX_HEALTH * (rand()%100/100)*25+75;
}

bool Colony::initialize(AntSim *gamePtr, int width, int height, int ncols,TextureManager *textureM)
{
	world = gamePtr;
	return Actor::initialize((Game*)gamePtr,width,height,ncols,textureM);
}

void Colony::die()
{
	alive = false;
	setActive(false);
}