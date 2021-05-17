#pragma once

#include "Game.h"
#include "View.h"
#include <iostream>
#include <functional>
#include <math.h>

using namespace std;
using namespace std::placeholders;

class Game;

class View;

class Controller
{
public:
	Controller();
	static Controller* get(Game* game, View* view, const char* control = "Human");
	~Controller();
};
