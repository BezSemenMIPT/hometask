#include "Controller.h"
#include "Dump.h"
#include "Human.h"
#include <string.h>

Controller* Controller :: get(Game* game, View* view, const char* control)
{
	if (strcmp(control, "Dump") == 0)
	{
		return new Dump(game, view);
	}
	else
	{
		return new Human(game, view, "wasd");
	}
}

Controller :: Controller()
{
};

Controller :: ~Controller()
{
};
