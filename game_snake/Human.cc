#include "Human.h"


void Human :: letter_control(int key)
{
	if (key == keys[0])
	{
		snake -> set_direct(UP);
	}
	if (key == keys[1])
	{
		snake -> set_direct(LEFT);
	}
	if (key == keys[2])
	{
		snake -> set_direct(DOWN);
	}
	if (key == keys[3])
	{
		snake -> set_direct(RIGHT);
	}
}

Human :: Human(Game* _game, View* _view, const char* _keys)
{
	game = _game;
	view = _view;
	keys = _keys;

	snake = &game -> make_snake();
	view -> setonkey(bind(&Human :: letter_control, this, _1));
}

Human :: ~Human()
{
}

