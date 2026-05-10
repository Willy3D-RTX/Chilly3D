#ifndef C3D_ENGINE
#define C3D_ENGINE 101

#define C3D_TITLE "Chilly3D"
#define C3D_VIDEO_W 480 // 480
#define C3D_VIDEO_H 270 // 270
#define C3D_VERSION_MAJOR (C3D_ENGINE / 100)
#define C3D_VERSION_MINOR (C3D_ENGINE - (C3D_VERSION_MAJOR * 100))

#define C3D_BUFFER_SIZE 255

#include "platform.h"

/// INDICE DE PROTOTIPOS
/// ====================
void c3d_init(void);
void c3d_quit();
void c3d_info(const char *text, ...);
void c3d_error(const char *text, ...);
bool c3d_run(void);
void c3d_event(void);
void c3d_present(void);

void c3d_init(void)
{
	root.flags.debug = true;
	root.error = -1;

	c3d_info("Iniciando %s Ver %d.%d...", C3D_TITLE, C3D_VERSION_MAJOR, C3D_VERSION_MINOR);

	#if (C3D_PLATFORM == C3D_PLATFORM_LINUX)
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) == 0)
	{
		c3d_error("SDL_Init()");
		c3d_quit();
	}

	window = SDL_CreateWindow(C3D_TITLE, root.video.width, root.video.height, 0);
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

	root.run = true;

	#endif // (C3D_PLATFORM == C3D_PLATFORM_LINUX)
}

void c3d_quit()
{
	if (render != nullptr)
	{
		c3d_info("Destruir render...");
		SDL_DestroyRenderer(render);
	}

	if (window != nullptr)
	{
		c3d_info("Destruir la ventana...");
		SDL_DestroyWindow(window);
	}

	exit(root.error);
}

void c3d_info(const char *text, ...)
{
	if (root.flags.debug == false) { return; }
	va_list arg;
	char str[C3D_BUFFER_SIZE];
	va_start(arg, text);
	vsprintf(str, text, arg);
	va_end(arg);
	printf("[ i ] @%s: %s.\n", C3D_TITLE, str);
}

void c3d_error(const char *text, ...)
{
	va_list arg;
	char str[C3D_BUFFER_SIZE];
	va_start(arg, text);
	vsprintf(str, text, arg);
	va_end(arg);
	printf("[ e ] @%s: %s.\n", C3D_TITLE, str);
}


bool c3d_run(void)
{
	return (root.run);
}


void c3d_event(void)
{
	#if (C3D_PLATFORM == C3D_PLATFORM_LINUX)
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_EVENT_QUIT)
		{
			root.run = false;
		}
	}
	#endif // C3D_PLATFORM == C3D_PLATFORM_LINUX)
}

void c3d_present(void)
{
	#if (C3D_PLATFORM == C3D_PLATFORM_LINUX)
	SDL_RenderPresent(render);
	#endif // C3D_PLATFORM == C3D_PLATFORM_LINUX)
}

#endif // C3D_ENGINE
