#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "Character.h"
#include "Texture.h"
#include "SpriteSheet.h"
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
			Character* test = new Character(window, 300.0, 400.0);
			Texture* dot1 = new Texture(window, 200.0, 400.0);
			Texture* dot2 = new Texture(window, 200.0, 200.0);
			Texture* background = new Texture(window, 0, 0);

			//Load the textures
			test->getSpriteSheet()->loadFromFile("Images/Luffy.png");
			dot1->loadFromFile("Images/dot.bmp");
			dot2->loadFromFile("Images/dot.bmp");
			background->loadFromFile("Images/bg.png");

			//Make the background transparent for the dots
			dot1->makeBackgroundTransparent();
			dot2->makeBackgroundTransparent();
			test->getSpriteSheet()->makeBackgroundTransparent();
			
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

				//Render the textures on the window
				background->render();
				test->getSpriteSheet()->render();
				dot1->render();
				dot2->render();
				
				//Update screen
				SDL_RenderPresent(window->getRenderer());
			}
			//Free ressources
			//delete test;
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