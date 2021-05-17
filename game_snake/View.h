#pragma once

#include <utility>
#include <functional>

//#using timer_fn = std::fun

using namespace std;


using timer_fn = function<void(void)>;
using key_fn = function<void(int)>;
struct timer
{
  timer_fn fn;
  int interval;
  int life_time;
};

class View
{
	public:
	View();
	static View* get(const char* tui_or_gui = "Tui");
	~View();

	virtual void addtimer(timer_fn fun, int interval) = 0;

	virtual void runloop() = 0;
	virtual void quit() = 0;
	virtual void setonkey(key_fn fun) = 0;

	virtual void draw_frame() = 0;
	virtual void draw_cell(pair<int, int> coordinates, int color) = 0;
	virtual void clean_cell(pair<int, int> coordinates) = 0;
	// TODO: virtual void draw_rabbit(const & r)=0;
	virtual pair<int, int> get_screen_size() const = 0;

};
