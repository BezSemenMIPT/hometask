#pragma once
#include <utility>
#include <list>

#include <stdlib.h>
#include <ctime>

#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>

#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#include <stdio.h>

#include <sys/poll.h>
#include <termios.h>


using namespace std;

class View;

class Rabbit
{
public:
	Rabbit(coord coordinates);
	coord get_coordinates();
	~Rabbit();
private:
	coord _coordinates;
};

class Snake
{
public:
	Snake(coord snake_head);
	void set_direct(int direction);
	list<coord> get_coordinates();
	coord get_snake_head();
	int get_direct();
	void update(coord head);
	~Snake();
private:
	list <coord> _coordinates;
	int direct;
};

class Game
{
public:
	Game(View* view);
	list<Snake> get_snake_list();
	list<Rabbit> get_rabbit_list();
	list <coord> get_snake_coordinates(Snake& snake);
	coord get_rabbit_coordinates(Rabbit& rabbit);
	Snake* get_snake();
	Rabbit& make_rabbit();
	Snake& make_snake();
	void update_snake();
	~Game();
private:
	View* view;
	list <Rabbit> rabbits;
	list<Snake> snakes;
	//list<pair<int, int>> obstacles;
	coord make_coordinates();
	//void make_obsracles();
//	int is_cell_obsracles(pair<int, int> cell);
};
