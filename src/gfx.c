#include "declarations.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>

#include <time.h>

int width = 1200;
int height = 1000;
char* name = "Trace";

static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_Texture* buffer;

int main()
{
	// Initialize GFX
	initGFX();

	// Run game loop
	for (;;)
	{
		// Check for events
		updateSDL();

		// Render
		doGFX();
	}
}

void initGFX()
{
	// Create a single SDL window
	window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

	// Create SDL Renderer for use in the window
	renderer = SDL_CreateRenderer(window, -1, 0);

	// Create SDL Texture to store the back buffer
	buffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);

	// Turn off showing of normal mouse cursor
	SDL_ShowCursor(SDL_DISABLE);
}

void doGFX()
{
	// Create memmory allocation to store pixels
	int* pixels =  (int*)malloc(width * height * sizeof(Uint32));

	// Store pixels in back buffer
	SDL_UpdateTexture(buffer, NULL, pixels, width * sizeof(Uint32));

	// Draw scene
	int x;
	int y;

	clock_t t = clock() / 5000;
	for (x = 0; x < width; x += 1)
	{
		for (y = 0; y < height; y += 1)
		{
			unsigned r = 0xFF & ((int)((1 + sin((x+t) / 10)) * 128));
			unsigned b = 0xFF & ((int)((1 + tan(y / 10)) * 128));
			pixels[x+y*width] = (r << 16) | (0 << 8) | b;
		}
	}

	// Free memmory allocation used to store pixels
	free(pixels);
	pixels = NULL;

	// Render back buffer to SDL Window
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, buffer, NULL, NULL);
	SDL_RenderPresent(renderer);

	// Update SDL
	updateSDL();
}

void updateSDL()
{
	// Check for SDL Events
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		// Check the type of the event
		switch(event.type)
		{
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				switch(event.key.keysym.sym)
				{
					//case 'w': wsad[0] = ev.type==SDL_KEYDOWN; break;
					//case 's': wsad[1] = ev.type==SDL_KEYDOWN; break;
					//case 'a': wsad[2] = ev.type==SDL_KEYDOWN; break;
					//case 'd': wsad[3] = ev.type==SDL_KEYDOWN; break;
					case SDLK_ESCAPE: stopGFX();
					default: break;
				}
				break;
			case SDL_QUIT: stopGFX();
		}
	}
	int x,y;
	SDL_GetRelativeMouseState(&x,&y);
}

void stopGFX()
{
	SDL_Quit();
	exit(0);
}

