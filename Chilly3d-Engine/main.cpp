#include "c3d/engine.h"

int main()
{
	c3d_init();
	c3d_video_init(C3D_ENGINE_WIDTH, C3D_ENGINE_HEIGHT);

	while (c3d_run())
	{
		c3d_event();
		c3d_video_clear(c3d_video_rgb565(8, 16, 32));
		c3d_video_pixel(root.video.width/2, root.video.height/2, c3d_video_rgb565(255, 255, 255));
		c3d_draw_line(0, 0, 100, 100, c3d_video_rgb565(255, 255, 0));
		c3d_video_present();
	}

	c3d_quit();
	return (0);
}
