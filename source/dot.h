#ifndef DOT
#define DOT

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>

/*Constant variables*/
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The dimensions of the dot
static const int DOT_WIDTH = 20;
static const int DOT_HEIGHT = 20;

//The maximum velocity of the dot
static const int DOT_VEL = 10;

class Dot
{
public:
	
	//Initialize the variables
	Dot();

	~Dot();
	//Takes the key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);
	//Moves the dot
	void move(float timeStep);
	//Shows the dot on the screen
	void render();

private:
	//
	//Position of the dot on the x and y axis 
	float posX_, posY_;
	//Velocity of the dot on the x and y axis
	float velX_, velY_;
};


#endif
