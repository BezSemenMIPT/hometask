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

using namespace std;

class Tui :public View
{
private:
	static function<void(void)> onwinch;
	static void winch(int n);

	bool running;
	pair<timer_fn, int> timer;
	list<key_fn> keys;
	struct termios _termios;
public:
	Tui();
	void draw_frame();
	void draw_ver_lines(struct winsize ws);
	void draw_hor_line(struct winsize ws);
	void draw_cell(coord coordinates, int collor) const;
	void clean_cell(coord coordinates) const;
	pair<int, int> get_screen_size() const;
	void addtimer(timer_fn fun, int interval);
	void setonkey(key_fn fun);
	void runloop();
	void quit();
	~Tui();
};
