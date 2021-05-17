#pragma once

#include "Controller.h"

class Human:public Controller
{
public:
	Human(Game* _game, View* _view, const char* _keys = "WASD");
	void letter_control(int key);
	~Human();
private:
	const char* keys;
	Game* game;
	Snake* snake;
	View* view;
};
