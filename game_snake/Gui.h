#pragma once

#include "View.h"
#include <SFML/Graphics.hpp>
#include <list>
#include <utility>
#include <string>
#include<unistd.h>

using namespace std;


class Gui:public View
{
private:
	list<pair<const char*, pair<int, int>>> to_print;
	pair<timer_fn,int> t;
	list<key_fn> keys;
	sf::Clock clock;
public:
	Gui();
	void addtimer(timer_fn fun, int interval);

	void runloop();
	void quit();
	void setonkey(key_fn fun);

	void draw_frame();
	void draw_cell(const pair<int, int> coordinates, int color);
	void clean_cell(const pair<int, int> coordinates);

	pair<int, int> get_screen_size() const;	
	
	sf::RenderWindow window;

	~Gui();
};

