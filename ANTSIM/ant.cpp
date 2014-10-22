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
	lastFrame = Behavior::DEFAULT;
	cooldown = 0;
	name = "Ant";
	pher = nullptr;
}

Ant::~Ant() {
}

void Ant::wanderAimlessly(float frameTime)
{
	//dont set new direction every frame
	if(rand()%100>80){
		//set new direction in front of ant
		direction += ((rand()%10)/10.0)*PI/4 - PI/8;
	}

	D3DXVECTOR2 aim(antNS::ANT_SPEED,0);
	float nx = cos(direction)*aim.x - sin(direction)*aim.y;
	float ny = sin(direction)*aim.x + cos(direction)*aim.y;
	aim.x = nx; aim.y=ny;
	aim += *getCenter();

	moveInDirection(aim,frameTime);
}

void Ant::hungryAction(float frameTime)
{
	

	VECTOR2 currentDestination(-1,-1);
	float strongestSignal = -1;
	float distanceToClosest = 999999999999999;
	for(int i = 0 ; i < antNS::NUM_SIMULTANEOUS_SIGNALS; i++)
	{
		//types of signals to consider
		if(signals[i].getType()==SignalType::food || signals[i].getType()==SignalType::colony_food)
		{
			//if the new signal is closer, use that
			VECTOR2 distToSignal = signals[i].getData()-*getCenter();
			float currentDistanceSqrd = distToSignal.x*distToSignal.x + distToSignal.y*distToSignal.y;

			//go to the larger priority, or go to the closest
			if(signals[i].getPriority() > strongestSignal || (signals[i].getPriority() == strongestSignal && currentDistanceSqrd<distanceToClosest))
			{
				//set destination, reset distance
				currentDestination = signals[i].getData();
				strongestSignal=signals[i].getPriority();
				distanceToClosest = currentDistanceSqrd;
			}
			
		}//get largest priority
	}//for


	

	if(currentDestination == VECTOR2(-1,-1))
	{
		//beg
		if(pher==nullptr){
			pher=world->spawnPher(*getCenter(),Signal(SignalType::beg,*getCenter(),species));
		}
		else
		{
			pher->refresh();
			pher->setSignal(Signal(SignalType::beg,*getCenter()));
		}

		wanderAimlessly(frameTime);
	}
	else
	{
		moveInDirection(currentDestination,frameTime);
	}


}

void Ant::defaultAction(float frameTime)
{
	if(pher == nullptr)
	{
		pher = world->spawnPher(*getCenter(),Signal(SignalType::ant_nearby,*getCenter(),species));
	}
	else
	{
		pher->refresh();
		pher->setSignal(Signal(SignalType::ant_nearby,*getCenter(),species));
	}

	VECTOR2 currentDestination(-1,-1);
	float strongestSignal = -1;
	float distanceToClosest = 999999999999999;
	for(int i = 0 ; i < antNS::NUM_SIMULTANEOUS_SIGNALS; i++)
	{
		//types of signals to consider
		if(signals[i].getType()!=SignalType::null && signals[i].getSpecies()!=species)
		{
			//if the new signal is closer, use that
			VECTOR2 distToSignal = signals[i].getData()-*getCenter();
			float currentDistanceSqrd = distToSignal.x*distToSignal.x + distToSignal.y*distToSignal.y;

			//go to the larger priority, or go to the closest
			if(signals[i].getPriority() > strongestSignal || (signals[i].getPriority() == strongestSignal && currentDistanceSqrd<distanceToClosest))
			{
				//set destination, reset distance
				currentDestination = signals[i].getData();
				strongestSignal=signals[i].getPriority();
				distanceToClosest = currentDistanceSqrd;
			}
			
		}//get largest priority
	}//for

	//if a valid destination was found
	if(strongestSignal > -1)
		moveInDirection(currentDestination,frameTime);

	//wander aimlessly
	else
	{
		wanderAimlessly(frameTime);
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
		if(foodLevel < 0){
			health -= antNS::STARVATION_DAMAGE * frameTime;
			foodLevel = 0;
		}

		//determine behavior
		if(foodLevel < antNS::STOMACH_SIZE *0.25) behavior = Behavior::BEGGING;
		else behavior = Behavior::DEFAULT;


		if(lastFrame != behavior)
		{
			pher = nullptr;
			lastFrame = behavior;
		}

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
	if(!isUnderground && getActive()) Actor::draw(color);
}


void Ant::create(VECTOR2 location,Species spc)
{
	setCenterLocation(location);
	age = 0;
	isUnderground = false;
	species = spc;
	setActive(true);
	isMale = (rand()%2);
	direction = ((rand()%10)/10.0)*2*PI;
	foodLevel = antNS::STOMACH_SIZE;
	alive = true;
	health = antNS::ANT_MAX_HEALTH * (rand()%100/100.0)*25+75;
	pher = nullptr;

	switch (species)
	{
	case BLACK:
		color = graphicsNS::BLACK;
		break;
	case RED:
		color = graphicsNS::RED;
		break;
	case UNKNOWN:
		color = graphicsNS::LTGRAY;
		break;
	default:
		color = graphicsNS::WHITE;
		break;
	}
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
		//if friendly
		if(species == ant->species)
		{
			if(ant->getBehavior()==Behavior::BEGGING && foodLevel > antNS::STOMACH_SIZE/2)
			{
				foodLevel -= ant->receiveFood(foodLevel-antNS::STOMACH_SIZE/2);
			}
		}
		else
		{
			//if we can attack
			if(cooldown == 0)
			{
				ant->damage(((rand()%100)/100.0)*antNS::ATTACK_DAMAGE_RANGE+antNS::ATTACK_MIN_DAMAGE);
				cooldown += antNS::ATTACK_COOLDOWN;
			}
		}
	}

	Pheromone * pher =  dynamic_cast<Pheromone*>(other);
	if(pher!=NULL)
	{
		receiveSignal(pher->getSignal());
	}

	Colony * colony =  dynamic_cast<Colony*>(other);
	if(colony!=NULL)
	{
		//request to fill stomach
		foodLevel += colony->requestFood(antNS::STOMACH_SIZE-foodLevel);
	}
}


float Ant::receiveFood(float avalible)
{
		float emptySpace = antNS::STOMACH_SIZE - foodLevel;
		avalible = min(emptySpace,avalible);
		foodLevel += avalible;
		return avalible;
		//
}

void Ant::moveInDirection(VECTOR2 dir,float frameTime)
{
	//if we have a valid destination
	if(dir != *getCenter())
	{
		//get vector from this to dest
		dir -= *getCenter();
		D3DXVec2Normalize(&dir,&dir);
		dir *= antNS::ANT_SPEED*frameTime;
		setCenterLocation(*getCenter()+dir);
		//point ant in direction
		setRadians(atan2(dir.y,dir.x));
		
		//moving means an ant loses control of its pheromone
		if(pher!=nullptr)
			pher->setCenterLocation(*getCenter());
	}
}