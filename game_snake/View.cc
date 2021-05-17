#include "View.h"
#include "Tui.h"
#include "Gui.h"
#include <string.h>


View* View :: get(const char* tui_or_gui)
{
	if (strcmp(tui_or_gui, "Tui") == 0)
	{
		return new Tui;
	}
	else
	{
		return new Gui;
	}
}

View :: View()
{
};

View :: ~View()
{
};
