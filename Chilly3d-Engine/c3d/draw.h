#ifndef C3D_DRAW
#define C3D_DRAW

void c3d_draw_line(int x0, int y0, int x1, int y1, uint16_t color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);

	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;

	int err = dx - dy;

	while (1)
	{
		c3d_video_pixel(x0, y0, color);

		if (x0 == x1 && y0 == y1)
			break;

		int e2 = err * 2;

		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}

		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void c3d_draw_triangles(
	int x0, int y0,
	int x1, int y1,
	int x2, int y2,
	uint16_t color
)
{
	c3d_draw_line(x0, y0, x1, y1, color);
	c3d_draw_line(x1, y1, x2, y2, color);
	c3d_draw_line(x2, y2, x0, y0, color);
}

void c3d_draw_rect(
	int x0, int y0,
	int x1, int y1,
	uint16_t color
)
{
	c3d_draw_line(x0, y0, x1, y0, color);
	c3d_draw_line(x1, y0, x1, y1, color);
	c3d_draw_line(x1, y1, x0, y1, color);
	c3d_draw_line(x0, y1, x0, y0, color);
}

#endif // C3D_DRAW
