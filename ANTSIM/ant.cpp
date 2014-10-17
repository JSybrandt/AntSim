#include "ant.h"

Ant::Ant():Actor()
{
	age = 0;
	isUnderground = false;
	isMale = true;
	direction = 0;
	foodLevel = antNS::STOMACH_SIZE;
	alive = false;
	setActive(false);
}

Ant::~Ant()
{
}

void Ant::update(float frameTime)
{
	if(getActive())
	{
		//age
		age += frameTime;
		if(age > antNS::LIFE_EXPECTANCY) health -= antNS::OLD_AGE_DAMAGE * frameTime;
		
		
		//eat food
		foodLevel -= antNS::METABOLISM*frameTime;
		if(foodLevel < 0) health -= antNS::STARVATION_DAMAGE * frameTime;
		
		//dont set new direction every frame
		if(rand()%100>80){
			//set new direction in front of ant
			direction += ((rand()%1000)/1000.0)*PI/4 - PI/8;
		}

		D3DXVECTOR2 aim(1,0);
		float nx = cos(direction)*aim.x - sin(direction)*aim.y;
		float ny = sin(direction)*aim.x + cos(direction)*aim.y;
		aim.x = nx; aim.y=ny;
		aim *= antNS::ANT_SPEED*frameTime;

		setCenterLocation(*getCenter() + aim);

		//move
		setRadians(direction);

		if(health <= 0) die();

		

	}
}

void Ant::draw()
{
	if(!isUnderground && getActive()) Actor::draw();
}

void Ant::create(VECTOR2 location)
{
	setCenterLocation(location);
	age = 0;
	isUnderground = false;
	setActive(true);
	isMale = (rand()%2);
	direction = ((rand()%1000)/1000.0)*2*PI;
	foodLevel = antNS::STOMACH_SIZE;
	alive = true;
	health = antNS::ANT_MAX_HEALTH * (rand()%100/100)*25+75;
}

bool Ant::initialize(AntSim *gamePtr, int width, int height, int ncols,TextureManager *textureM)
{
	world = gamePtr;
	return Actor::initialize((Game*)gamePtr,width,height,ncols,textureM);
}

void Ant::die()
{
	//TODO:leave dead bodies, use animation
	alive = false;
	setActive(false);
}

void Ant::receiveSignal(Signal s)
{
	//TODO: change behavior based on signal;
}