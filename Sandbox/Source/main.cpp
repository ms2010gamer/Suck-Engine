#include "Suck.h"


int main()
{
	Window window("Test", 800, 600, false);

	while (!window.isWindowClosed())
	{
		window.clear();

		window.update();
	}
	
	window.destroy();
	return 0;
}