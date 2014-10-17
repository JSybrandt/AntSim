#include "ant.h"
#include "antSim.h"

Ant::Ant():Actor()
{
	age = 0;
	isUnderground = false;
	isMale = true;
	direction = 0;
	foodLevel = antNS::STOMACH_SIZE;
	alive = false;
	setActive(false);
	signalIndex = 0;
	behavior = Behavior::DEFAULT;
	cooldown = 0;
}

Ant::~Ant()
{
}

void Ant::hungryAction(float frameTime)
{
	//beg
	if(cooldown == 0){
		world->spawnPher(*getCenter(),Signal(SignalType::beg,*getCenter()));
		cooldown += antNS::COOLDOWN;
	}

	VECTOR2 closestFood = *getCenter();
	float distanceToClosestFoodSqrd = 999999999999999;

	for(int i = 0 ; i < antNS::NUM_SIMULTANEOUS_SIGNALS; i++)
	{
		if(signals[i].getType()==SignalType::food)
		{
			VECTOR2 distToFood = signals[i].getData()-*getCenter();
			float currentDistanceSqrd = distToFood.x*distToFood.x + distToFood.y*distToFood.y;
			if(currentDistanceSqrd < distanceToClosestFoodSqrd)
			{
				closestFood = distToFood;
			}
		}
	}

	//if we have a valid destination
	if(closestFood != *getCenter())
	{
		D3DXVec2Normalize(&closestFood,&closestFood);
		closestFood *= antNS::ANT_SPEED*frameTime;
		setCenterLocation(*getCenter()+closestFood);
		setRadians(atan2(closestFood.y,closestFood.x));
	}


}

void Ant::defaultAction(float frameTime)
{
	VECTOR2 currentDestination(-1,-1);
	float strongestSignal = 0;
	for(int i = 0 ; i < antNS::NUM_SIMULTANEOUS_SIGNALS; i++)
	{
		if(signals[i].getPriority() > strongestSignal)
		{
			currentDestination = signals[i].getData();
			strongestSignal=signals[i].getPriority();
		}
	}
	//if we have a valid destination
	if(currentDestination.x>0&&currentDestination.y>0)
	{
		//get vector from this to dest
		currentDestination -= *getCenter();
		D3DXVec2Normalize(&currentDestination,&currentDestination);
		currentDestination *= antNS::ANT_SPEED*frameTime;
		setCenterLocation(*getCenter()+currentDestination);
		setRadians(atan2(currentDestination.y,currentDestination.x));
	}
	//wander aimlessly
	else
	{
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
	}
}

void Ant::update(float frameTime)
{
	if(getActive())
	{
		if(cooldown > 0) cooldown -= frameTime;
		if(cooldown <= 0) cooldown = 0;

		//age
		age += frameTime;
		if(age > antNS::LIFE_EXPECTANCY) health -= antNS::OLD_AGE_DAMAGE * frameTime;

		//eat food
		foodLevel -= antNS::METABOLISM*frameTime;
		if(foodLevel < 0) health -= antNS::STARVATION_DAMAGE * frameTime;


		//determine behavior
		if(foodLevel < antNS::STOMACH_SIZE *0.25) behavior = Behavior::BEGGING;
		else behavior = Behavior::DEFAULT;


		if(behavior == Behavior::DEFAULT)
		{
			defaultAction(frameTime);
		}
		if(behavior == Behavior::BEGGING)
		{
			hungryAction(frameTime);
		}
		

		//reset signals
		for(int i = 0 ; i < antNS::NUM_SIMULTANEOUS_SIGNALS; i++)
		{
			signals[i] = Signal();
		}

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
	for(int i = 0 ; i < antNS::NUM_SIMULTANEOUS_SIGNALS; i++)
	{
		if(signalIndex >= antNS::NUM_SIMULTANEOUS_SIGNALS) signalIndex = 0;
		if(signals[signalIndex].getType() == SignalType::null)
		{
			signals[signalIndex] = s;
			break;
		}
		signalIndex++;
	}
}

void Ant::touches(Actor* other)
{
	Food* food = dynamic_cast<Food*>(other);
	if(food != NULL)
	{
		//request to fill stomach
		foodLevel += food->eat(antNS::STOMACH_SIZE-foodLevel);
	}

	Ant* ant = dynamic_cast<Ant*>(other);
	if(ant != NULL)
	{
		if(ant->getBehavior()==Behavior::BEGGING && foodLevel > antNS::STOMACH_SIZE/2)
		{
			foodLevel -= ant->receiveFood(foodLevel-antNS::STOMACH_SIZE/2);
		}
	}
}


float Ant::receiveFood(float avalible)
{
		float emptySpace = antNS::STOMACH_SIZE - foodLevel;
		avalible = min(emptySpace,avalible);
		foodLevel += avalible;
		return avalible;
}