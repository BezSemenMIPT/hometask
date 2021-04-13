#include "Gui.h"

void Gui::addtimer(timer_fn fun, int interval)
{
	//
}

void Gui::runloop()
{
	//
}

void Gui::quit()
{
	//
}

void Gui::setonkey(key_fn fun)
{
	//
}

void Gui::draw_frame()
{
	//
}

void Gui::draw_cell(pair<int, int> coordinates, int color) const
{
	//
}

void Gui::clean_cell(pair<int, int> coordinates) const
{
	//
}

pair<int, int> Gui::get_screen_size() const
{
	//
	return make_pair(0, 0);
}

Gui::Gui()
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		// window.draw(...);

		// end the current frame
		window.display();
	}
}

Gui :: ~Gui()
{
	//
}