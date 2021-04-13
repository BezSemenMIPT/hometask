#include "Tui.h"

using namespace std;

function<void(void)> Tui::onwinch;

void Tui::addtimer(timer_fn fun, int interval)
{
	timer.first = fun;
	timer.second = interval;
}

void Tui::setonkey(key_fn fun)
{
	keys.push_back(fun);
}


void Tui::runloop()
{
	struct pollfd fds = { 0, POLL_IN, 0 };
	int interval = timer.second;
	running = true;
	int flag = 1;
	while (running)
	{
		int poll_return = poll(&fds, 1, flag * interval);
		flag = 1;
		if (poll_return == 0)
		{
			timer.first();
		}
		else
		{
			flag = 0;
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
  	printf("\e[H");
	printf("\e[J");
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

void Tui::draw_hor_line(struct winsize ws) 
{
	for (int i = 0; i < ws.ws_col; i++) {
		printf("%c", '#');
	}
}

void Tui::draw_ver_lines(struct winsize ws) 
{
	for (int i = 0; i < ws.ws_row-4; i++) 
	{	
		printf("\e[E");
		printf("%c", '#');
		for (int i = 0; i < ws.ws_col-2; i++) 
		{
		  printf("%c", ' ');
		}
		printf("%c", '#');
	}
	printf("\e[E");
}


void Tui::draw_frame() 
{
	struct winsize ws;
	clean_screen();
	ioctl(0, TIOCGWINSZ, &ws);
	draw_hor_line(ws);
	draw_ver_lines(ws);
	draw_hor_line(ws);
}

#if 0
void Tui::draw_frame()
{
	clean_screen();
	printf("\e[47m"); //set white background

	//draw frame
	printf("\e[0;0H"); //set cursor to the top left
	for (int i = 0; i < get_screen_size().second; i++)
	{
		printf(" ");
	}
	for (int i = 0; i < get_screen_size().first - 4; i++)
	{
		printf("\n");
		printf(" ");
		for (int j = 0; j < get_screen_size().second - 1; j++)
		{
			printf("\e[C"); //cursor shift
		}
		printf(" ");
	}
	printf("\n");
	for (int i = 0; i < get_screen_size().second; i++)
	{
		printf(" ");
	}
	printf("\n");


	printf("\e[0m"); //set normal background
}
#endif

void Tui::draw_cell(coord coordinates, int collor) const
{
	printf("\e[%d;%dH", coordinates.y, coordinates.x - 1);
	printf("\e[%dm", collor); //set cell background
	printf(" ");
	printf("\e[0m"); //set normal background

	printf("\e[%d;%dH", get_screen_size().first - 1, 0);
};

void Tui::clean_cell(coord coordinates) const
{
	printf("\e[%d;%dH", coordinates.y, coordinates.x - 1);
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

	draw_frame();
	onwinch = bind(&Tui::draw_frame, this);
	signal(SIGWINCH, &Tui::winch);
};

Tui :: ~Tui()
{
	tcsetattr(STDIN_FILENO, TCSANOW, &_termios);
};
