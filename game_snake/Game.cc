#include "Game.h"
#include "View.h"

#define SNAKE_AMOUNT 2
#define SNAKE_SIZE 5
#define RABBITS_COUNT 15


using namespace std;

coord Rabbit::get_coordinates()
{
	return _coordinates;
}

Rabbit::Rabbit(coord get_coordinates)
{
	_coordinates = get_coordinates;
}

Rabbit::~Rabbit()
{

};

void Snake::set_direct(int direction)
{
	direct = direction;
}

Snake::Snake(coord snake_head)
{
	int size_x=get_screen_size().x;
	coord tmp;
	tmp.y=snake_head.y;
	if (snake_head.x > size_x)
	{
		for (int i = 1; i < SNAKE_SIZE; i++)
		{
			tmp.x=snake_head.x+i;
			_coordinates.push_back(tmp);
		}
		direct = LEFT;
	}
	else
	{
		for (int i = 1; i < SNAKE_SIZE; i++)
		{
			tmp.x=snake_head.x-i;
			_coordinates.push_back(tmp);
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
	int x = rand() % (view->get_screen_size().x - 7) + 1;
	int y = rand() % (view->get_screen_size().y - 3) + 1;
	coord tmp;
	tmp.x=x;
	tmp.y=y;
	return tmp;
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
			head.y++;
			break;
		case LEFT:
			head.y--;
			break;
		case UP:
			head.x--;
			break;
		case DOWN:
			head.x++;
			break;
		}
		view->draw_snake_head(head, snake.get_direct());
		view->clean_cell(snake.get_coordinates().front());//back
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

	snakes.push_back(Snake(snake_head));
	return snakes.back();
}



Game::Game(View* _view)
{

	view = _view;
	srand(time(NULL));

	for (int i = 0; i < SNAKE_AMOUNT; i++)
	{
		make_snake();
	}

	for (int i = 0; i < RABBITS_COUNT; i++)
	{
		make_rabbit();
	}

	for (Rabbit& rabbit : get_rabbit_list())
	{
		_view->draw_rabbit(get_rabbit_coordinates(rabbit));
	}


	//Get snake coordinates and draw it
	for (Snake& snake : get_snake_list())
	{
	  for(coord tmp : get_snake_coordinates(snake))
	  {
	    view->draw_snake_body(tmp);
	  }
	  view->draw_snake_head(snake.get_snake_head());//TODO
	}

	view->addtimer(bind(&Game::update_snake, this), 200);
};


Game :: ~Game()
{
	rabbits.clear();
	snakes.clear();
};
