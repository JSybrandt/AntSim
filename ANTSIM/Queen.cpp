#include "ant.h"
#include "antSim.h"
#include "Queen.h"

Queen::Queen():Ant(){

	age = 0;
	AntSim* world;
	isUnderground = true;
	foodLevel = antNS::QUEEN_STOMACH_SIZE;
	alive = false;
	setActive(false);
	signalIndex = 0;
	behavior = Behavior::DEFAULT;
	pher = nullptr;
	cooldown = 0;
}

Queen::~Queen(){

}

void Queen::create(VECTOR2 location,Species spc)
{
	setCenterLocation(location);
	age = 0;
	species = spc;
	isUnderground = true;
	setActive(true);
	foodLevel = antNS::QUEEN_STOMACH_SIZE;
	alive = true;
	health = antNS::QUEEN_MAX_HEALTH;
}

float Queen::receiveFood(float avalible)
{
		float emptySpace = antNS::QUEEN_STOMACH_SIZE - foodLevel;
		avalible = min(emptySpace,avalible);
		foodLevel += avalible;
		return avalible;
}

void Queen::die()
{
	alive = false;
	setActive(false);
}

void Queen::hungryAction(float frameTime)
{
	//beg
	if(pher == nullptr){
		pher = world->spawnPher(*getCenter(),Signal(SignalType::queen,*getCenter()));
	}
	else{
		pher->refresh();
		pher->setSignal(Signal(SignalType::queen,*getCenter()));
	}

}

void Queen::defaultAction(float frameTime){

	VECTOR2 location;
	Reproduce(location, species);

	if(pher == nullptr)
	{
		pher = world->spawnPher(*getCenter(),Signal(SignalType::queen,*getCenter(),species));
	}
	else
	{
		pher->refresh();
		pher->setSignal(Signal(SignalType::queen,*getCenter(),species));
	}

}

void Queen::update(float frameTime){
	if(getActive())
	{
		if(cooldown > 0) cooldown -= frameTime;
		if(cooldown <= 0) cooldown = 0;

		//age
		age += frameTime;
		if(age > antNS::QUEEN_LIFE_EXPECTANCY) health -= antNS::OLD_AGE_DAMAGE * frameTime;

		//eat food
		foodLevel -= antNS::METABOLISM*frameTime;
		if(foodLevel < 0) health -= antNS::STARVATION_DAMAGE * frameTime;


		//determine behavior
		if(foodLevel < antNS::QUEEN_STOMACH_SIZE *0.25) behavior = Behavior::BEGGING;
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

void Queen::draw()
{
	if(!isUnderground && getActive()) Actor::draw();
}

bool Queen::initialize(AntSim *gamePtr, int width, int height, int ncols,TextureManager *textureM)
{
	world = gamePtr;
	return Actor::initialize((Game*)gamePtr,width,height,ncols,textureM);
}

void Queen::receiveSignal(Signal s)
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

void Queen::touches(Actor* other)
{
	Food* food = dynamic_cast<Food*>(other);
	if(food != NULL)
	{
		//request to fill stomach
		foodLevel += food->eat(antNS::QUEEN_STOMACH_SIZE-foodLevel);
	}

	Queen* queen = dynamic_cast<Queen*>(other);
	if(queen != NULL)
	{
		if(queen->getBehavior()==Behavior::BEGGING && foodLevel > antNS::QUEEN_STOMACH_SIZE/2)
		{
			foodLevel -= queen->receiveFood(foodLevel-antNS::QUEEN_STOMACH_SIZE/2);
		}
	}

	Pheromone * pher =  dynamic_cast<Pheromone*>(other);
	if(pher!=NULL)
	{
		receiveSignal(pher->getSignal());
	}

}


void Queen::Reproduce(VECTOR2 location,Species spc){
	 world->spawnAnt(location,spc);
}