#include <iostream>
#include <SDL.h>

//Starts up SDL and creates window
bool init();
//Loads media
bool loadMedia();
//
void close();


int main(int argc, char** argv)
{
	
	if (SDL_Init(SDL_INIT_VIDEO != 0))
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Quit();
	
	return 0;
}