#pragma once
#include "view.h"


class tui :public view {
	void clear_screen();
	void draw_hor_line(struct winsize);
	void draw_ver_lines(struct winsize);
public:
	tui();
	void draw();
	void run();
};
