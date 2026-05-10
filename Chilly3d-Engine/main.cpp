#include "c3d/engine.h"

int main()
{
	c3d_init();

	while (c3d_run())
	{
		c3d_event();
		c3d_present();
	}

	c3d_quit();
	return (0);
}
