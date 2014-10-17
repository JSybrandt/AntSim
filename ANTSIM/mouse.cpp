#include "mouse.h"

Actor test;

Mouse::Mouse()
{
	target = new Actor;
	collisionType = CIRCLE;
	radius = 10;
	selectedItem = -1;	//nothing return
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
	Actor::draw();
}


bool Mouse::initialize(AntSim *gamePtr, Input *in, Graphics *g, int width, int height, int ncols)
{
	//target = gamePtr.ants[0];
	world = gamePtr;
	input = in;
	graphics = g;
	menuAnchor = VECTOR2(0,0);
	verticalOffset = 10;
	linePtr = 1;
	selectedItem = -1;
	menuItemFont = new TextDX();
	menuHeadingFont = new TextDX();
	menuItemFontHighlight = new TextDX();
	data.clear();
	data.push_back("Ant");
	data.push_back("Health: 100");
	data.push_back("Food: 37");
	data.push_back("Age: 5");
	if(menuItemFont->initialize(graphics, 15, true, false, "Calibri") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuItem font"));
	if(menuItemFontHighlight->initialize(graphics, 18, true, false, "Calibri") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuItem font"));
	if(menuHeadingFont->initialize(graphics, 25, true, false, "Calibri") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuHeading font"));



	//return Actor::initialize((Game*)gamePtr,width,height,ncols,textureM);
	return true;
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