#include "Game.h"
#include "View.h"

#define SNAKE_SIZE 5
#define RABBITS_COUNT 15

#define RABBIT 41
#define SNAKE 42
#define SNAKE_HEAD 43

using namespace std;

coord Rabbit::get_coordinates()
{
	return _coordinates;
}

Rabbit::Rabbit(coord get_coordinates)
{
	_coordinates = get_coordinates;
}

Rabbit :: ~Rabbit()
{
};

void Snake::set_direct(int derection)
{
	direct = derection;
}

Snake::Snake(coord snake_head, int wight)
{
	if (snake_head.first > wight)
	{
		for (int i = 1; i < SNAKE__SIZE; i++)
		{
			_coordinates.push_back(make_pair(snake_head.x + i, snake_head.y));
		}
		direct = LEFT;
	}
	else
	{
		for (int i = 1; i < SNAKE_SIZE; i++)
		{
			_coordinates.push_back(make_pair(snake_head.x - i, snake_head.y));
		}
		direct = RIGHT;
	}
};

Snake :: ~Snake()
{
};


coord Game::get_rabbit_coordinates(Rabbit& rabbit)
{
	return rabbit.get_coordinates();
}

list<coord> Game::get_snake_coordinates(Snake& snake)
{
	return snake.get_coordinates();
}


coord Game::make_coordinates()
{
	int x = rand() % (view->get_screen_size().y - 3) + 3;
	int y = rand() % (view->get_screen_size().x - 5) + 3;
	return make_pair(x, y);
};

list<Snake> Game::get_snake_list()
{
	return snakes;
}

list<Rabbit> Game::get_rabbit_list()
{
	return rabbits;
}

list <coord> Snake::get_coordinates()
{
	return _coordinates;
};

coord Snake::get_snake_head()
{
	return _coordinates.front();
}

int Snake::get_direct()
{
	return direct;
}

void Game::update_snake()
{
	for (Snake& snake : snakes)
	{
		coord head = snake.get_snake_head();
		switch (snake.get_direct())
		{
		case RIGHT:
			head.first++;
			break;
		case LEFT:
			head.first--;
			break;
		case UP:
			head.second--;
			break;
		case DOWN:
			head.second++;
			break;
		}
		view->draw_cell(snake.get_snake_head(), SNAKE);
		view->draw_cell(head, SNAKE_HEAD);
		view->clean_cell(snake.get_coordinates().back());
		snake.update(head);
	}
}

void Snake::update(coord head)
{
	_coordinates.push_front(head);
	_coordinates.pop_back();
}

Rabbit& Game::make_rabbit()
{
	coord rabbit = make_coordinates();
	rabbits.push_back(rabbit);
	return rabbits.back();
}

Snake& Game::make_snake()
{
	coord snake_head = make_coordinates();
	if (snake_head.x < SNAKE_sIZE + 2)
	{
		snake_head.x = SNAKE_SIZE + 2;
	}
	if (snake_head.x > view->get_screen_size().y - SNAKE_SIZE - 1)
	{
		snake_head.x = view->get_screen_size().y - SNAKE_SIZE - 1;
	}
	snakes.push_back(Snake(snake_head, view->get_screen_size().y / 2));
	return snakes.back();
}



Game::Game(View* _view)
{

	view = _view;
	srand(time(NULL));

	//make Rabbits
	for (int i = 0; i < RABBITS_COUNT; i++)
	{
		make_rabbit();
	}

	for (Rabbit& rabbit : get_rabbit_list())
	{
		_view->draw_cell(get_rabbit_coordinates(rabbit), RABBIT);
	}

	//Get snake coordinates and draw it
	for (Snake& snake : get_snake_list())
	{
		for (coord it : get_snake_coordinates(snake))
		{
			view->draw_cell(it, (it != get_snake_coordinates(snake).front()) * SNAKE + (it == get_snake_coordinates(snake).front()) * SNAKE_HEAD);
		}
	}


	view->addtimer(bind(&Game::update_snake, this), 200);
};


Game :: ~Game()
{
	rabbits.clear();
	snakes.clear();
};
