#pragma once

#include "View.h"

#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>

#include <sys/poll.h>

#include <functional>
#include <utility>

#include <list>

#include <termios.h>
#include <time.h>
#include <algorithm>

using namespace std;



class Tui:public View
{
private:
	static function<void(void)> onwinch;
	static void winch(int n);
	
	bool running;
	list<timer> timers;
	list<key_fn> keys;
	struct termios _termios;
public:
	Tui();
	void draw_frame();
	void draw_cell(pair <int, int> coordinates, int collor);
	void clean_cell(pair <int, int> coordinates);
	pair<int, int> get_screen_size() const;
	void addtimer(timer_fn fun, int interval);
	void setonkey(key_fn fun);
	void runloop();
	void quit();
	~Tui();
};
