#ifndef C3D_PLATFORM
#define C3D_PLATFORM -1

#define C3D_PLATFORM_LINUX 0
#define C3D_PLATFORM_MACOS 1
#define C3D_PLATFORM_WIN32 2
#define C3D_PLATFORM_WIN64 3
#define C3D_PLATFORM_ESP32 4
#define C3D_PLATFORM_ESPS3 5
#define C3D_PLATFORM_ESPP4 6
#define C3D_PLATFORM_RPI32 7
#define C3D_PLATFORM_RPI64 8
#define C3D_PLATFORM_ANDROID 9
#define C3D_PLATFORM_OTHER 10

/* detectar plataforma */

#if defined(__linux__)
	#undef C3D_PLATFORM
	#define C3D_PLATFORM C3D_PLATFORM_LINUX

#elif defined(_WIN64)
	#undef C3D_PLATFORM
	#define C3D_PLATFORM C3D_PLATFORM_WIN64

#elif defined(_WIN32)
	#undef C3D_PLATFORM
	#define C3D_PLATFORM C3D_PLATFORM_WIN32

#elif defined(__APPLE__)
	#undef C3D_PLATFORM
	#define C3D_PLATFORM C3D_PLATFORM_MACOS

#elif defined(__ANDROID__)
	#undef C3D_PLATFORM
	#define C3D_PLATFORM C3D_PLATFORM_ANDROID

#elif defined(ESP_PLATFORM)
	#undef C3D_PLATFORM
	#define C3D_PLATFORM C3D_PLATFORM_ESP32

#else
	#undef C3D_PLATFORM
	#define C3D_PLATFORM C3D_PLATFORM_OTHER

#endif // defined(__linux__)

#if (C3D_PLATFORM == C3D_PLATFORM_LINUX)
	#include <SDL3/SDL.h>
	#include <SDL3_image/SDL_image.h>
	#include <SDL3_mixer/SDL_mixer.h>
	#include <SDL3_ttf/SDL_ttf.h>

	#include <stdio.h>
	#include <stdlib.h>
	#include <stdarg.h>
	#include <cstdint>

	SDL_Window *window = nullptr;
	SDL_Renderer *render = nullptr;
	SDL_Event event;
	SDL_Surface *surface = nullptr;
	SDL_Texture *texture = nullptr;
#endif // (C3D_PLATFORM == C3D_PLATFORM_LINUX)

struct root
{
	int platform = C3D_PLATFORM;
	int error = 0;

	bool run = false;

	struct flags
	{
		bool debug = false;
		bool c3d = false;
	} flags;

	struct video
	{
		uint16_t front_buffer[C3D_ENGINE_WIDTH * C3D_ENGINE_HEIGHT]; /// RGB565 = 16BITS
		uint16_t back_buffer[C3D_ENGINE_WIDTH * C3D_ENGINE_HEIGHT]; /// RGB565 = 16BITS

		uint16_t width = C3D_ENGINE_WIDTH;
		uint16_t height = C3D_ENGINE_HEIGHT;

		struct fps
		{
			uint16_t frame = 0;
			uint16_t total = 0;
			uint64_t time = 0;
		} fps;
	} video;
} root;

#endif // C3D_PLATFORM
