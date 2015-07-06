#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "Texture.h"
#include "Window.h"
#include "Timer.h"

using namespace std;

/***Prototypes***/
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
	//The main window
	Window* window = new Window();

	//The main timer
	Timer timer;

	//Start up SDL and create window
	if (!init())
	{
		cout << "Failed to initialize SDL!" << endl;
	}
	else
	{
		//Initialize the main window
		if (!window->init())
		{
			cout << "Failed to initialize window!" << endl;
		}
		else
		{ 
			//Create the textures
			Texture* dot1 = new Texture(200.0, 400.0);
			Texture* dot2 = new Texture(200.0, 200.0);

			//Load the textures
			dot1->loadFromFile(window, "Images/dot.bmp");
			dot2->loadFromFile(window, "Images/dot.bmp");
			
			//Link the collision boxes
			dot1->addCollisionBox(dot2->getCollisionBox());

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
					else
					{
						//Handle keyboard inputs
						dot1->handleEvent(e);
					}
				}
				//Calculate the time to render each frame
				float timeStep = timer.getTicks() / 1000.f;

				//Move the texture 
				dot1->move(timeStep);
				timer.start();
				
				//Initialize renderer color
				SDL_SetRenderDrawColor(window->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);

				//Clear screen
				SDL_RenderClear(window->getRenderer());

				//Render the texture on the window
				dot1->render(window);
				dot2->render(window);
				
			
				//Update screen
				SDL_RenderPresent(window->getRenderer());
			}
			//Free ressources
			delete dot1;
			delete dot2;
			delete window;
			window = 0;
			dot1 = 0;
			dot2 = 0;
		}
	}

	//Close SDL
	
	close();
	
	return 0;
}