#pragma once

#include "Controller.h"
//#include "Game.h"

class Dump:public Controller
{
public:
	Dump(Game* _game, View* _view);
	void controller();
	void make_target();
	~Dump();
private:
	Game* game;
	Snake* snake;
	View* view;
	int distance(pair<int, int> a, pair<int, int> b);
	Rabbit& get_near_rabbit();
	pair<int, int> target;
};
