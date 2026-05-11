#ifndef C3D_VIDEO
#define C3D_VIDEO

void c3d_video_init(uint16_t _width, uint16_t _height)
{
	if (root.flags.c3d == false)
	{
		c3d_error("Inicia primero c3d_init()!");
		return;
	}

	root.error = -1;

	c3d_info("VIDEO: %dx%d", _width, _height);

	root.video.width = _width;
	root.video.height = _height;

	#if (C3D_PLATFORM == C3D_PLATFORM_LINUX)
	window = SDL_CreateWindow(C3D_ENGINE_TITLE, root.video.width, root.video.height, SDL_WINDOW_FULLSCREEN);
	if (window == nullptr)
	{
		c3d_error("SDL_CreateWindow()");
		c3d_quit();
	}

	render = SDL_CreateRenderer(window, 0);
	if (render == nullptr)
	{
		c3d_error("SDL_CreateRenderer()");
		c3d_quit();
	}
	#endif // (C3D_PLATFORM == C3D_PLATFORM_LINUX)

	root.error = 0;
}

void c3d_video_present(void)
{
	root.video.fps.frame++;
	#if (C3D_PLATFORM == C3D_PLATFORM_LINUX)
	if (SDL_GetTicks() > root.video.fps.time)
	{
		root.video.fps.total = root.video.fps.frame;
		root.video.fps.frame = 0;
		root.video.fps.time = SDL_GetTicks() + 1000;
		if (root.flags.debug == true)
		{
			char str[C3D_BUFFER_ZISE];
			sprintf(str, "%s, FPS=%d", C3D_ENGINE_TITLE, root.video.fps.total);
			SDL_SetWindowTitle(window, str);
		}
	}

	if (texture != nullptr) { SDL_DestroyTexture(texture); }
	texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGB565, SDL_TEXTUREACCESS_STREAMING, root.video.width, root.video.height);
	memcpy(root.video.front_buffer, root.video.back_buffer, root.video.width * root.video.height * sizeof(uint16_t));
	SDL_UpdateTexture(texture, NULL, root.video.front_buffer, root.video.width * sizeof(uint16_t));
	SDL_RenderClear(render);
	SDL_RenderTexture(render, texture, NULL, NULL);

	SDL_RenderPresent(render);
	SDL_Delay(1000/60);  // retardo de 16ms.
	#endif // (C3D_PLATFORM == C3D_PLATFORM_LINUX)
}

uint16_t c3d_video_rgb565(uint8_t r, uint8_t g, uint8_t b)
{
	return (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3));
}

void c3d_video_pixel(int xpos, int ypos, uint16_t color)
{
	root.video.back_buffer[ypos * C3D_ENGINE_WIDTH + xpos] = color;
}

void c3d_video_clear(uint16_t color)
{
	int32_t total = root.video.width * root.video.height;
	for (int i = 0; i < total; i++) { root.video.back_buffer[i] = color; }
}

#endif // C3D_VIDEO
