#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "Texture.h"
#include "Window.h"

using namespace std;



/*Functions prototypes*/
//Starts up SDL
bool init();
//shuts down SDL
void close();



//Initialize SDL
bool init()
{
	//Initialization flag
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
		success = false;
	}
	
	return success;
}


//Quit SDL subsystems
void close()
{
	IMG_Quit();
	SDL_Quit();
}



int main(int argc, char** argv)
{
	Window* window = new Window();
	Texture* texture = new Texture("Images/dot.bmp");
	
	//Start up SDL and create window
	if (!init())
	{
		cout << "Failed to initialize SDL!" << endl;
	}
	else
	{
		//Initialize the window
		if (!window->init())
		{
			cout << "Failed to initialize window!" << endl;
		}
		else
		{ 
			//Load the textures
			if (!texture->loadFromFile(window))
			{
				cout << "Failed to load media!" << endl;
			}
			else
			{
				//Main loop flag
				bool quit = false;
				//Event handler
				SDL_Event  e;
				//While application is running
				while (!quit)
				{
					//Handle events on queue
					while (SDL_PollEvent(&e) != 0)
					{
						//User requests quit
						if (e.type == SDL_QUIT)
						{
							quit = true;
						}
					}		
					//Render the texture on the window
					texture->render(window);
				}
			}
		}
	}

	//Free ressources and close SDL
	delete texture;
	delete window;
	window = 0;
	texture = 0;
	close();
	
	return 0;
}