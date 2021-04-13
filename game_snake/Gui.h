#pragma once
#include "View.h"
#include <SFML/Graphics.hpp>

using namespace std;

class Gui :public View
{
public:
	Gui();
	void addtimer(timer_fn fun, int interval);
	void runloop();
	void quit();
	void setonkey(key_fn fun);

	void draw_frame();
	void draw_cell(coord coordinates, int color) const;
	void clean_cell(coord coordinates) const;

	coord get_screen_size() const;

	~Gui();
};
