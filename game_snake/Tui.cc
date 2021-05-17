#include "Tui.h"
#include <time.h>

using namespace std;

function<void(void)> Tui::onwinch;

void Tui::addtimer(timer_fn fun, int interval)
{
	timer t;
	t.fn = fun;
	t.interval = interval;
	t.life_time = 0;
	timers.push_back(t);
}

void Tui::setonkey(key_fn fun)
{
	keys.push_back(fun);
}

bool minfn(const timer& a, const timer& b)
{
	return ((a.interval - a.life_time) < (b.interval - b.life_time));
}

int delta_time(struct timespec first, struct timespec second)
{
	return -first.tv_sec * 1000 + second.tv_sec * 1000 - first.tv_nsec / 1000000 + second.tv_nsec / 1000000;
}

void Tui::runloop()
{
	struct pollfd fds = { 0, POLL_IN, 0 };
	running = true;
	while (running)
	{
		struct timespec t1, t2;
		clock_gettime(CLOCK_MONOTONIC, &t1);
		int interval = min_element(timers.begin(), timers.end(), minfn)->interval;

		int poll_return = poll(&fds, 1, interval);
		clock_gettime(CLOCK_MONOTONIC, &t2);

		int delta = delta_time(t1, t2);

		for_each(timers.begin(), timers.end(), [delta](timer& t) {t.life_time += delta; });
		for_each(timers.begin(), timers.end(), [](timer& t) {
			if (t.life_time >= t.interval)
			{
				t.life_time = 0;
				t.fn();
			}
		});

		if (poll_return != 0)
		{
			char buf;
			read(0, &buf, 1);
			if (buf == 'q')
			{
				kill(getpid(), 9);
			}
			for (auto fun : keys)
			{
				fun(buf);
			}
		}
	}
}

void Tui::quit()
{
	running = false;
}

void clean_screen()
{
	printf("\e[2J"); //clean sreen
};

void Tui::winch(int n)
{
	onwinch();
};

pair<int, int> Tui::get_screen_size() const
{
	struct winsize screen_size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &screen_size);
	return make_pair(screen_size.ws_row, screen_size.ws_col);
}

void Tui::draw_frame()
{
	//
}


void Tui::draw_cell(pair<int, int> coordinates, int collor)
{
	printf("\e[%d;%dH", coordinates.second, coordinates.first - 1);
	printf("\e[%dm", collor); //set cell background
	printf(" ");
	printf("\e[0m"); //set normal background

	printf("\e[%d;%dH", get_screen_size().first - 1, 0);
};

void Tui::clean_cell(pair<int, int> coordinates)
{
	printf("\e[%d;%dH", coordinates.second, coordinates.first - 1);
	printf("\e[0m"); //set normal background
	printf(" ");

	printf("\e[%d;%dH", get_screen_size().first - 1, 0);
}

Tui::Tui()
{
	struct termios newt, _termios;
	tcgetattr(STDIN_FILENO, &_termios);
	newt = _termios;
	newt.c_lflag &= ~ICANON;
	newt.c_lflag &= ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	clean_screen();
	onwinch = bind(&Tui::draw_frame, this);
	signal(SIGWINCH, &Tui::winch);
};

Tui :: ~Tui()
{
	tcsetattr(STDIN_FILENO, TCSANOW, &_termios);
};
