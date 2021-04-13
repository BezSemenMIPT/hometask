#pragma once

#include "Controller.h"

class Dump :public Controller
{
public:
	Dump(Game* _game, View* _view);
	void controller();
	~Dump();
private:
	Game* game;
	Snake* snake;
	View* view;
	int distance(pair<int, int> a, pair<int, int> b);
	Rabbit& get_near_rabbit();
};