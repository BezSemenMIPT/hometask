#include "View.h"
#include "Game.h"
#include "Human.h"

#include <iostream>


using namespace std;

int main()
{

	View* graphics = View::get("Tui");

	Game* game = new Game(graphics);

	Human h_1(game, graphics,"ijkl");
	Human h_2(game, graphics, "wasd");



	graphics->runloop();

	return 0;
}
