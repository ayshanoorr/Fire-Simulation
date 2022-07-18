#include <iostream>
#include <vecmath.h>
#include <GL/glew.h>
#include "SDL2/SDL.h"
#include "Window.h"
#include "Particle.h"
using namespace std;

const int W_WIDTH = 600;
const int W_HEIGHT = 500;

int main()
{	
	// WINDOW CREATION
	Window window(W_WIDTH, W_HEIGHT);

	if (window.Init() == false)
		return 0;	
	
	// MAIN LOGIC
	int prev_time = SDL_GetTicks();
	int particle_num = 1000;
	Particle particles[particle_num];
	
	while (true)
	{
		int elapsed;
		// unsigned char green = (unsigned char)((1 + sin(elapsed * 0.001)) * 128);
		
		for(int i = 0; i < particle_num; i++)
		{
			Vector4f col = particles[i].getCol();
			Vector3f pos = particles[i].getPos();
			
			if (particles[i].getLifetime() > 0)
			{	
				window.SetPixel(W_WIDTH - pos.x(), W_HEIGHT - pos.y(), col.x() * 255, col.y() * 255, col.z() * 255);
				//elapsed = SDL_GetTicks() - prev_time;
				//prev_time = SDL_GetTicks();
				elapsed = SDL_GetTicks();
				particles[i].Update(elapsed);
			}
			else
			{
				particles[i].ReInitialize();
			}
		}
		
		//window.Blur();
		window.Update();
		
		//frame limiter
		if (elapsed < 1000/60)
		{
			SDL_Delay((1000/60) - elapsed);
		}
	
		if (window.ProcessEvents() == false)
		{
			break;
		}
	}
	
	window.Destroy();
	return 0;
}
