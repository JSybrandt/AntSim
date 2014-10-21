#include "mouse.h"

Actor test;

Mouse::Mouse()
{
	target = new Actor;
	collisionType = CIRCLE;
	radius = 1;
	menuAnchor = VECTOR2(0,0);
	verticalOffset = 10;
	linePtr = 1;
	selectedItem = -1;
	menuItemFont = new TextDX();
	menuHeadingFont = new TextDX();
	menuItemFontHighlight = new TextDX();
	data.clear();
	setScale(.25);

}

Mouse::~Mouse()
{
}

void Mouse::update(float frameTime) {
	std::string convert;
	setCenterX(input->getMouseX()); 
	setCenterY(input->getMouseY());


	data.clear();
	data.push_back(target->getName());
	if(target->getSpecies() == BLACK) {
		convert = "Species: Black";
		data.push_back(convert);
	}
	else if(target->getSpecies() == RED) {
		convert = "Species: Red";
		data.push_back(convert);
	}
	else { // if(target->getSpecies() == UNKNOWN)
		convert = "Species: Unknown";
		data.push_back(convert);
	}
	convert = "Health: ";
	convert += std::to_string(target->getHealth());
	data.push_back(convert);

	convert = "Food: ";
	convert += std::to_string(target->getFood());
	data.push_back(convert);
	convert = "Age: ";
	convert += std::to_string(target->getAge());
	data.push_back(convert);
}

void Mouse::draw()
{

	Actor::draw(graphicsNS::BLUE);
}


bool Mouse::initialize(AntSim *gamePtr, Graphics* graphics, int width, int height, int ncols, TextureManager* textureM) //Input *in, Graphics *g,
{
	//target = gamePtr.ants[0];
	world = gamePtr;

	//data.push_back("Ant");
	//data.push_back("Health: 100");
	//data.push_back("Food: 37");
	//data.push_back("Age: 5");
	if(menuItemFont->initialize(graphics, 15, true, false, "Calibri") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuItem font"));
	if(menuItemFontHighlight->initialize(graphics, 18, true, false, "Calibri") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuItem font"));
	if(menuHeadingFont->initialize(graphics, 25, true, false, "Calibri") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuHeading font"));



	return Actor::initialize((Game*)gamePtr,width,height,ncols,textureM);
	//return true;
}
//void Mouse::getInfo(Actor &ent) {
//	target = &ent;
//}
void Mouse::getInfo(Ant &ent) {
	target = &ent;
}
void Mouse::getInfo(Colony &ent) {
	target = &ent;
}

void Mouse::print() {
	setCenterX(input->getMouseX()); 
	setCenterY(input->getMouseY());
	menuAnchor = VECTOR2(spriteData.x+20,spriteData.y+5);
	for(int i = 0; i < data.size(); i++)
	{
		int foo =(i)*verticalOffset;
		menuItemFont->print(data.at(i), menuAnchor.x, menuAnchor.y+foo);
	}
}