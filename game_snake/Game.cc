#include "Game.h"
#include "View.h"

#define SNAKE_START_SIZE 7
#define RABBITS_COUNT 9

using namespace std;

pair<int, int> Rabbit::get_coordinates()
{
	return _coordinates;
}

Rabbit::Rabbit(pair<int, int> get_coordinates)
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

Snake::Snake(pair<int, int> snake_head, int wight)
{
	if (snake_head.first > wight)
	{
		for (int i = 1; i < SNAKE_START_SIZE; i++)
		{
			_coordinates.push_back(make_pair(snake_head.first + i, snake_head.second));
		}
		direct = LEFT;
	}
	else
	{
		for (int i = 1; i < SNAKE_START_SIZE; i++)
		{
			_coordinates.push_back(make_pair(snake_head.first - i, snake_head.second));
		}
		direct = RIGHT;
	}
};

Snake :: ~Snake()
{
};


pair<int, int> Game::get_rabbit_coordinates(Rabbit& rabbit)
{
	return rabbit.get_coordinates();
}

list<pair<int, int>> Game::get_snake_coordinates(Snake& snake)
{
	return snake.get_coordinates();
}


pair<int, int> Game::make_coordinates()
{
	int x = rand() % (view->get_screen_size().second - 3) + 3;
	int y = rand() % (view->get_screen_size().first - 5) + 3;
	return make_pair(x, y);
};

list<Snake>& Game::get_snake_list()
{
	return snakes;
}

list<pair<int, int>> Game::get_wall()
{
	return obstacles;
}

list<Rabbit>& Game::get_rabbit_list()
{
	return rabbits;
}

list <pair <int, int>> Snake::get_coordinates()
{
	return _coordinates;
};

pair<int, int> Snake::get_snake_head()
{
	return _coordinates.front();
}

int Snake::get_direct()
{
	return direct;
}

void Snake::eat_rabbit()
{
	_coordinates.push_back(get_snake_head());
}

void Game::check_shell_is_rabbit(Snake& snake)
{
	for (auto it = get_rabbit_list().begin(); it != get_rabbit_list().end(); ++it)
	{
		if (snake.get_snake_head() == get_rabbit_coordinates(*it))
		{
			view->clean_cell(get_rabbit_coordinates(*it));
			snake.eat_rabbit();
			remove_rabbit(it);
			Rabbit& r = make_rabbit();
			//view->draw_cell(get_rabbit_coordinates(r), 45);
			printf("\e[%d;%dH", get_rabbit_coordinates(r).second, get_rabbit_coordinates(r).first-1);//*******************
			printf("9");
			return;
		}
	}
}

void Game::update_snake()
{
	for (Snake& snake : snakes)
	{
		pair<int, int> head = snake.get_snake_head();
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
		view->clean_cell(snake.get_coordinates().back());
		view->draw_cell(snake.get_snake_head(), SNAKE);
		view->draw_cell(head, SNAKE_HEAD);
		snake.update(head);
		check_shell_is_rabbit(snake);
	}
}

void Snake::update(pair<int, int> head)
{
	_coordinates.push_front(head);
	_coordinates.pop_back();
}

Rabbit& Game::make_rabbit()
{
	pair<int, int> rabbit = make_coordinates();
	rabbits.push_back(rabbit);
	return rabbits.back();
}

Snake& Game::make_snake()
{
	pair<int, int> snake_head = make_coordinates();
	if (snake_head.first < SNAKE_START_SIZE + 2)
	{
		snake_head.first = SNAKE_START_SIZE + 2;
	}
	if (snake_head.first > view->get_screen_size().second - SNAKE_START_SIZE - 1)
	{
		snake_head.first = view->get_screen_size().second - SNAKE_START_SIZE - 1;
	}
	snakes.push_back(Snake(snake_head, view->get_screen_size().second / 2));
	return snakes.back();
}

int Game::get_obstacles(pair<int, int> shell)
{
	for (pair<int, int> it : obstacles)
	{
		if (it == shell)
		{
			return 1;
		}
	}
	for (Snake& snake : snakes)
	{
		for (pair<int, int> it : snake.get_coordinates())
		{
			if (it == shell)
			{
				return 1;
			}
		}
	}
	return 0;
}

void Game::remove_rabbit(list<Rabbit>::iterator target)
{

	rabbits.erase(target);
}

Game::Game(View* _view)
{
	view = _view;
	srand(time(NULL));
	//make Obstacles
	for (int i = 1; i < view->get_screen_size().second + 2; i++)
	{

		obstacles.push_back(make_pair(i, 1));
		obstacles.push_back(make_pair(i, view->get_screen_size().first - 2));
	}
	for (int j = 1; j < view->get_screen_size().first - 2; j++)
	{
		obstacles.push_back(make_pair(2, j));
		obstacles.push_back(make_pair(view->get_screen_size().second + 1, j));
	}
	//make Rabbits
	for (int i = 0; i < RABBITS_COUNT; i++)
	{
		make_rabbit();
	}
	//подписаться на таймер
	view->addtimer(bind(&Game::update_snake, this), 100);
};


Game :: ~Game()
{
	rabbits.clear();
	snakes.clear();
};
