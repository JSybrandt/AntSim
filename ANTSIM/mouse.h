#pragma once
#include "Actor.h"
#include "ant.h"
#include "colony.h"
#include <vector>

class AntSim;


class Mouse: public Actor
{
private:
	AntSim* world;
	Actor* target;
	TextDX *menuItemFont;
	TextDX *menuItemFontHighlight;
	TextDX *menuHeadingFont;
	VECTOR2 menuAnchor;
	std::vector<std::string> data;
	int verticalOffset;
    int linePtr;
	int selectedItem;

public:
	//Mouse(Actor& t);
	Mouse();
	~Mouse();
	void update(float frameTime);
	void draw();
	//void getInfo(Actor &ent);
	void getInfo(Ant &ent);
	void getInfo(Colony &ent);
	void print();
	bool initialize(AntSim *gamePtr, Input *in, Graphics *g, int width, int height, int ncols);
};