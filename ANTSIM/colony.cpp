#include "Colony.h"

#include "antSim.h"

#include "Queen.h"

Colony::Colony():Actor()
{
	age = 0;
	resetRate = colonyNS::BIRTHRATE;
	foodLevel = colonyNS::STOMACH_SIZE;
	alive = false;
	spawnCooldown = 0;
	setActive(false);
	//radius = .01;
	setScale(2);
	name = "Colony";
	pher = nullptr;
	queen = nullptr;
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
			pher = world->spawnPher(*getCenter(),Signal(SignalType::colony_food,*getCenter(),species));
		}
		else
		{
			pher->refresh();
			pher->setSize(pheromoneNS::COLONY_FOOD_RADIUS*(foodLevel/colonyNS::STOMACH_SIZE));
		}

		//Health, die.
		if(health <= 0) die();

		spawnCooldown -= frameTime;

		/*if(spawnCooldown <= 0)
		{
			world->spawnAnt(*getCenter(), getSpecies());
			spawnCooldown += resetRate;
		}*/
		

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
	queen = world->spawnQueen(location,species);

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


float Colony::requestFood(float amount)
{
	amount = min(amount,foodLevel);
	foodLevel-= amount;
	return amount;
}