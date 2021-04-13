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

#define LEFT -1
#define RIGHT 1
#define UP -2
#define DOWN 2

#define SNAKE 42
#define SNAKE_HEAD 43

using namespace std;

class View;

class Rabbit
{
public:
	Rabbit(pair<int, int> coordinates);
	pair<int, int> get_coordinates();
	~Rabbit();
private:
	pair<int, int> _coordinates;
};

class Snake
{
public:
	Snake(pair<int, int> snake_head, int wight);
	void set_direct(int derection);
	list<pair <int, int>> get_coordinates();
	pair<int, int> get_snake_head();
	int get_direct();
	void update(pair<int, int> head);
	~Snake();
private:
	list <pair<int, int>> _coordinates;
	int direct;
};

class Game
{
public:
	Game(View* view);
	list<Snake> get_snake_list();
	list<Rabbit> get_rabbit_list();
	list <pair <int, int>> get_snake_coordinates(Snake& snake);
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
