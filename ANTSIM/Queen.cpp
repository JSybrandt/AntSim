#include "ant.h"
#include "antSim.h"
#include "Queen.h"

Queen::Queen():Ant(){

	age = 0;
	AntSim* world;
	isUnderground = false;
	foodLevel = antNS::QUEEN_STOMACH_SIZE;
	alive = false;
	setActive(false);
	signalIndex = 0;
	behavior = Behavior::DEFAULT;
	pher = nullptr;
	cooldown = 0;
	name = "QUEEN";
}

Queen::~Queen(){

}

void Queen::create(VECTOR2 location,Species spc)
{
	setCenterLocation(location);
	age = 0;
	species = spc;
	isUnderground = false;
	setActive(true);
	foodLevel = antNS::QUEEN_STOMACH_SIZE;
	alive = true;
	health = antNS::QUEEN_MAX_HEALTH;
	color = graphicsNS::YELLOW;
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

	if(cooldown == 0){
		Reproduce(*getCenter(),species);
		cooldown += queenNS::BIRTH_RATE;
	}

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

bool Queen::initialize(AntSim *gamePtr, int width, int height, int ncols,TextureManager *textureM)
{
	world = gamePtr;
	return Actor::initialize((Game*)gamePtr,width,height,ncols,textureM);
}

void Queen::Reproduce(VECTOR2 location,Species spc){
	 world->spawnAnt(location,spc);
}