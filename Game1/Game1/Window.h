#ifndef WINDOW
#define WINDOW

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
//#include <SDL_tff.h>

using namespace std;


/*Constant variables*/
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


class Window 
{
public:
	//Initialize the variables
	Window();
	//Deallocates memory
	~Window();

	//Create the variables
	bool init();
	//Destroy the variables
	void close();

	//Loads a texture to the renderer
	SDL_Texture* loadTexture(string path, int& width, int& height);

	//Access to window
	SDL_Window* getWindow();
	//Access to renderer
	SDL_Renderer* getRenderer();

private:
	SDL_Window* window_;
	SDL_Renderer* renderer_;
};


#endif