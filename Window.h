#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <iostream>

#include "SDL2/SDL.h"
using namespace std;

class Window
{
	
private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	Uint32 *buffer;
	
public:
	int w_width, w_height;	

	Window(int, int);
	bool Init();
	void Blur();
	void Update();
	bool ProcessEvents();
	void SetPixel(int, int, Uint32, Uint32, Uint32);
	void Destroy();
};

#endif
