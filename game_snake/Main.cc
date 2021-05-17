#include "View.h"
#include "Game.h"
#include "Controller.h"


#include <iostream>

#define WALL 47
#define RABBIT 45
#define SNAKE 42
#define SNAKE_HEAD 43

using namespace std;

int main()
{
	setbuf(stdout, NULL);
	//Make_model

	View* paint = View :: get("Tui");

	Game* game = new Game(paint);
#if 0
	for (pair<int, int> it : game -> get_wall())
	{
		paint -> draw_cell(it, WALL);
	}
#endif
	//Get list of rabbits and draw it
	int i = 1;
	for (Rabbit& rabbit : game -> get_rabbit_list())
	{
		//paint -> draw_cell(game -> get_rabbit_coordinates(rabbit), RABBIT);
		printf("\e[%d;%dH", game->get_rabbit_coordinates(rabbit).second, game->get_rabbit_coordinates(rabbit).first-1);//*******************
		printf("%d",i);
		i++;
	}

	Controller :: get(game, paint, "Dump");
	Controller :: get(game, paint, "Dump");
	//Controller :: get(game, paint, "Human");
	


	//Get snake coordinates and draw it
	for (Snake& snake : game -> get_snake_list())
	{
		for(pair<int, int> it : game -> get_snake_coordinates(snake))
		{
			paint -> draw_cell(it, (it != game -> get_snake_coordinates(snake).front()) * SNAKE + (it == game -> get_snake_coordinates(snake).front()) * SNAKE_HEAD);
		}
	}

	paint -> runloop();

	return 0;
}
