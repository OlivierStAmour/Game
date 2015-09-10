#ifndef WINDOW
#define WINDOW

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>


using namespace std;

/*Constant variables*/
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

//The dimensions of the dot
static const int DOT_WIDTH = 20;
static const int DOT_HEIGHT = 20;

//The maximum velocity of the dot
static const int MAX_VEL = 640;



class Window 
{
public:
	//Initialize the variables
	Window();
	//Deallocates memory
	~Window();

	//Create the variables
	bool init();

	//Move camera
	void moveCamera(float texturePositionX, float texturePositionY);

	//Destroy attributes
	void close();

	//Access to window
	SDL_Window* getWindow();

	//Access to renderer
	SDL_Renderer* getRenderer();

	//Access to camera
	SDL_Rect* getCamera();

private:
	SDL_Window* window_;
	SDL_Renderer* renderer_;
	SDL_Rect* camera_;
};


#endif
