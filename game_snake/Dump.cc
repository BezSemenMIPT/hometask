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
		if (distant != 0 && distant < distance(snake->get_snake_head(), game->get_rabbit_coordinates(near)))
		{
			near = rabbit;
		}
	}
	return near;
}

void Dump::controller()
{
	pair<int, int> head = snake->get_snake_head();

	make_target();
	if (head.second == target.second && snake->get_direct() == DOWN)
	{
		snake->set_direct(RIGHT);
	}
	else
		if (head.second == target.second && snake->get_direct() == UP)
		{
			snake->set_direct(LEFT);
		}
		else
			if (head.first == target.first && snake->get_direct() == RIGHT)
			{
				snake->set_direct(UP);
			}
			else
				if (head.first == target.first && snake->get_direct() == LEFT)
				{
					snake->set_direct(DOWN);
				}

	if (game->get_obstacles(make_pair(head.first, head.second + 1)) && snake->get_direct() == DOWN)
	{
		snake->set_direct(RIGHT);
	}
	else if (game->get_obstacles(make_pair(head.first, head.second - 1)) && snake->get_direct() == UP)
	{
		snake->set_direct(LEFT);
	}
	else if (game->get_obstacles(make_pair(head.first + 1, head.second)) && snake->get_direct() == RIGHT)
	{
		snake->set_direct(UP);
	}
	else if (game->get_obstacles(make_pair(head.first - 1, head.second)) && snake->get_direct() == LEFT)
	{
		snake->set_direct(DOWN);
	}
}

void Dump::make_target()
{
	target = game->get_rabbit_coordinates(get_near_rabbit());
}

Dump::Dump(Game* _game, View* _view)
{
	game = _game;
	view = _view;

	snake = &game->make_snake();
	target = game->get_rabbit_coordinates(get_near_rabbit());
	view->addtimer(bind(&Dump::controller, this), 100);
}

Dump :: ~Dump()
{
}
