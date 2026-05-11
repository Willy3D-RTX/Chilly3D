#ifndef C3D_ENGINE
#define C3D_ENGINE 100

#define C3D_ENGINE_TITLE "Chilly3D-Engine"
#define C3D_ENGINE_WIDTH 480
#define C3D_ENGINE_HEIGHT 270
#define C3D_ENGINE_VERSION_MAJOR (C3D_ENGINE / 100)
#define C3D_ENGINE_VERSION_MINOR (C3D_ENGINE - (C3D_ENGINE_VERSION_MAJOR * 100))

#define C3D_BUFFER_ZISE 255

#include "platform.h"

/// INDICE DE PROTOTIPOS
/// ====================
void c3d_init(void);
void c3d_quit(void);
void c3d_info(const char *text, ...);
void c3d_error(const char *text, ...);
void c3d_event(void);
bool c3d_run(void);

void 			c3d_video_init(uint16_t _width, uint16_t _height);
void 			c3d_video_present(void);
uint16_t		c3d_video_rgb565(uint8_t r, uint8_t g, uint8_t b);
void			c3d_video_pixel(int xpos, int ypos, uint16_t color);
void			c3d_video_clear(uint16_t color);

void c3d_draw_line(int x0, int y0, int x1, int y1, uint16_t color);

/// LIBRERIAS
/// =========
#include "video.h"
#include "draw.h"


void c3d_init(void)
{
	root.flags.debug = true;
	root.error = -1;
	c3d_info("Iniciando %s, Version %d.%d", C3D_ENGINE_TITLE, C3D_ENGINE_VERSION_MAJOR, C3D_ENGINE_VERSION_MINOR);

	#if (C3D_PLATFORM == C3D_PLATFORM_LINUX)
	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		c3d_error("SDL_Init()");
		c3d_quit();
	}
	root.flags.c3d = true;
	#endif // (C3D_PLATFORM == C3D_PLATFORM_LINUX)

	root.run = true;
	root.error = 0;
}

void c3d_quit(void)
{
	c3d_info("Cerrando %s..", C3D_ENGINE_TITLE);

	#if (C3D_PLATFORM == C3D_PLATFORM_LINUX)
	if (texture != nullptr)
	{
		c3d_info("Destruyendo texture..");
		SDL_DestroyTexture(texture);
	}

	if (surface != nullptr)
	{
		c3d_info("Destruyendo surface..");
		SDL_DestroySurface(surface);
	}

	if (render != nullptr)
	{
		c3d_info("Destruyendo render..");
		SDL_DestroyRenderer(render);
	}

	if (window != nullptr)
	{
		c3d_info("Destruyendo window..");
		SDL_DestroyWindow(window);
	}

	SDL_Quit();
	exit(root.error);
	#endif // (C3D_PLATFORM == C3D_PLATFORM_LINUX)
}

void c3d_info(const char *text, ...)
{
	if (root.flags.debug == false) { return; }
	va_list arg;
	char str[C3D_BUFFER_ZISE];
	va_start(arg, text);
	vsprintf(str, text, arg);
	va_end(arg);
	printf("[ I ] @%s: %s\n", C3D_ENGINE_TITLE, str);
}

void c3d_error(const char *text, ...)
{
	va_list arg;
	char str[C3D_BUFFER_ZISE];
	va_start(arg, text);
	vsprintf(str, text, arg);
	va_end(arg);
	printf("[ E ] @%s: %s\n", C3D_ENGINE_TITLE, str);
}

void c3d_event(void)
{
	#if (C3D_PLATFORM == C3D_PLATFORM_LINUX)
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_EVENT_QUIT)
		{
			c3d_info("Se cerro el motor %s", C3D_ENGINE_TITLE);
			root.run = false;
		}

		if (event.type == SDL_EVENT_KEY_DOWN)
		{
			if (event.key.key == SDLK_F12)
			{
				c3d_info("Se presiono el boton de salida de emergencia F12!");
				root.run = false;
			}
		}
	}
	#endif // (C3D_PLATFORM == C3D_PLATFORM_LINUX)
}

bool c3d_run(void)
{
	return (root.run);
}

#endif // C3D_ENGINE
