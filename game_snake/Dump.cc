#include "Dump.h"

//#define ON_CLOCK_ARROW 1

int Dump::distance(pair<int, int> a, pair<int, int> b)
{
	return fabs(a.first - b.first) + fabs(a.second - b.second);
}

Rabbit& Dump::get_near_rabbit()
{
	Rabbit& near = game->get_rabbit_list().front();

	for (Rabbit& rabbit : game->get_rabbit_list())
	{
		int distant = distance(snake->get_snake_head(), game->get_rabbit_coordinates(rabbit));
		if (distant > distance(snake->get_snake_head(), game->get_rabbit_coordinates(near)))
		{
			near = rabbit;
		}
	}
	return near;
}

void Dump::controller()
{
	//	Rabbit& rabbit = get_near_rabbit;
		//
}

Dump::Dump(Game* _game, View* _view)
{
	game = _game;
	view = _view;

	snake = &game->make_snake();
	view->addtimer(bind(&Dump::controller, this), 150);
}

Dump :: ~Dump()
{
}