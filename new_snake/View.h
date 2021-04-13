#pragma once
#include <utility>
#include <functional>

//#using timer_fn = std::fun

using namespace std;

struct coord
{
  int x;
  int y;
};


using timer_fn = function<void(void)>;
using key_fn = function<void(int)>;
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
	virtual void draw_cell(coord coordinates, int color) const = 0;
	virtual void clean_cell(coord coordinates) const = 0;

	virtual pair<int, int> get_screen_size() const = 0;

};
