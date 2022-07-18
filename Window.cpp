#include "Window.h"

Window::Window(int width, int height) : window(NULL), renderer(NULL), texture(NULL) 
{
	w_width = width;
	w_height = height;
}

bool Window::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		cout << "SDL Init Failed!" << endl;
		return 0;
	}
	
	// Creating SDL window
	window = SDL_CreateWindow("CG Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
								    w_width, w_height, SDL_WINDOW_SHOWN);
	
	if (window == NULL) // If window failed to initialize
	{
		cout << "SDL Window is NULL!" << endl;
		SDL_Quit();
		return 0;
	}
	
	// Creating SDL renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	
	if (renderer == NULL) // If renderer failed to initialize
	{
		cout << "SDL Renderer is NULL!" << endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 0;
	}
	
	// Creating SDL texture
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, w_width, w_height);
	
	if (texture == NULL) // If texture failed to initialize
	{
		cout << "SDL Texture is NULL!" << endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 0;
	}
	
	// Buffer allocation
	buffer = new Uint32[w_width * w_height];
	
	// Setting color value for pixels
	memset(buffer, 0, w_width * w_height * sizeof(Uint32));
	
	Update();
	
	return true;
}

void Window::Blur()
{
	Uint32 *buffer1 = new Uint32[w_width * w_height];
	
	swap(buffer, buffer1);

	for (int y = 0; y < w_height; y++) 
	{
		for (int x = 0; x < w_width; x++) 
		{
			int redTotal = 0;
			int greenTotal = 0;
			int blueTotal = 0;

			for (int row = -1; row <= 1; row++) 
			{
				for (int col = -1; col <= 1; col++) 
				{
					int currentX = x + col;
					int currentY = y + row;

					// only handle pixels within the screen

					if (currentX >= 0 && currentX < w_width && currentY >= 0 && currentY < w_height) 
					{
						Uint32 color = buffer1[currentY * w_width + currentX]; // the current pixel color

						// get the rgb components of the above color
						Uint8 red = color >> 24;
						Uint8 green = color >> 16;
						Uint8 blue = color >> 8;

						redTotal += red;
						greenTotal += green;
						blueTotal += blue;
					}
				}
			}

			Uint8 red = redTotal / 9;
			Uint8 green = greenTotal / 9;
			Uint8 blue = blueTotal / 9;

			SetPixel(x, y, red, green, blue);
		}
	}
}

void Window::Update()
{
	// Updating texture according to buffer
	SDL_UpdateTexture(texture, NULL, buffer, w_width * sizeof(Uint32));
	
	// Clearing previous value and creating copy for further use
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

bool Window::ProcessEvents()
{
	SDL_Event event;
	
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			return false;
	}
	
	return true;
}

void Window::SetPixel(int x, int y, Uint32 r, Uint32 g, Uint32 b)
{
	Uint32 color = 0;
	
	color += r;
	color <<= 8;
	color += g;
	color <<= 8;
	color += b;
	color <<= 8;
	color += 0xFF;
	
	buffer[(y * w_width) + x] = color;
}

void Window::Destroy()
{
	// Unallocating memory
	delete [] buffer;
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
