#include "Dot.h"

Dot::Dot()
{
	//Initialize the position
	posX_ = 0;
	posY_ = 0;
	//Initialize the velocity
	velX_ = 0;
	velY_ = 0;
}



Dot::~Dot()
{

}



void Dot::handleEvent(SDL_Event& e)
{
	//If a key is pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			velY_ += DOT_VEL;
			break;
		case SDLK_DOWN:
			velY_ -= DOT_VEL;
			break;
		case SDLK_RIGHT:
			velX_ += DOT_VEL;
			break;
		case SDLK_LEFT:
			velX_ -= DOT_VEL;
			break;
		}
	}
}



void Dot::move(float timeStep)
{
	//Adjust the position on the X axis
	posX_ += velX_;
	//If the dot is too far on the left or right
	if (posX_ < 0 || (posX_ + DOT_WIDTH) < SCREEN_WIDTH)
	{
		//move back
		posX_ -= velX_;
	}
	//Adjust the position on the Y axis
	posY_ += velY_;
	//If the dot is too far up or down
	if (posY_ < 0 || (posY_ + DOT_HEIGHT) < SCREEN_HEIGHT)
	{
		//move back
		posY_ -= velY_;
	}
}



void Dot::render()
{
	

}