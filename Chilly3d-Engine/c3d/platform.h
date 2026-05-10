#ifndef C3D_PLATFORM
#define C3D_PLATFORM -1

#define C3D_PLATFORM_LINUX 0
#define C3D_PLATFORM_WIN32 1
#define C3D_PLATFORM_WIN64 1
#define C3D_PLATFORM_MACOS 2
#define C3D_PLATFORM_ANDROID 3
#define C3D_PLATFORM_ESP32 4
#define C3D_PLATFORM_ESP32S3 5
#define C3D_PLATFORM_ESP32P4 6
#define C3D_PLATFORM_RPI32 7
#define C3D_PLATFORM_RPI64 8
#define C3D_PLATFORM_OTHERS 9


#if (__linux__)
	#undef C3D_PLATFORM
	#define C3D_PLATFORM C3D_PLATFORM_LINUX
#endif // (__linux__)


#if (C3D_PLATFORM == C3D_PLATFORM_LINUX)
	#include <SDL3/SDL.h>

	#include <stdio.h>
	#include <stdlib.h>
	#include <stdarg.h>

	SDL_Window *window = nullptr;
	SDL_Renderer *render = nullptr;
	SDL_Event event;
#endif // (C3D_PLATFORM == C3D_PLATFORM_LINUX)

struct root
{
	int platform = C3D_PLATFORM;
	int error = 0; /// Si es 0 es que no hay errores.

	bool run = false;

	struct flags
	{
		bool debug = false;
	} flags;

	struct video
	{
		uint16_t width = C3D_VIDEO_W;
		uint16_t height = C3D_VIDEO_H;
	} video;
} root;

#endif // C3D_PLATFORM
