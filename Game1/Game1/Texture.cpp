#include "Texture.h"



Texture::Texture()
{
	texture_ = NULL;

	posX_ = 0.0;
	posY_ = 0.0;

	velX_ = 0;
	velY_ = 0;

	width_ = 0;
	height_ = 0;

	path_ = "";
}

Texture::Texture(float posX, float posY)
{
	texture_ = NULL;

	posX_ = posX;
	posY_ = posY;

	velX_ = 0;
	velY_ = 0;

	width_ = 0;
	height_ = 0;

	path_ = "";
}


Texture::~Texture()
{
	free();
}



void Texture::free()
{
	if (texture_ != NULL)
	{
		SDL_DestroyTexture(texture_);
		texture_ = NULL;
		posX_ = 0.0;
		posY_ = 0.0;
		velX_ = 0;
		velY_ = 0;
		width_ = 0;
		height_ = 0;
	}
}



bool Texture::loadFromFile(Window* window, string path) 
{
	//Loading success flag
	bool success = true;
	path_ = path;
	//Load PNG texture from the renderer in the window
	texture_ = window->loadTexture(path_, width_, height_);
	if (texture_ == NULL)
	{
		cout << "Failed to load image!" << endl;
		success = false;
	}
	return success;
}



void Texture::render(Window* window, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{	
	SDL_Rect renderQuad = { (int)posX_, (int)posY_, (int)width_, (int)height_};

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render texture to screen
	SDL_RenderCopyEx(window->getRenderer(), texture_, clip, &renderQuad, angle, center, flip);
}



void Texture::handleEvent(SDL_Event& e)
{
	//If a key is pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			velY_ -= MAX_VEL;
			break;
		case SDLK_DOWN:
			velY_ += MAX_VEL;
			break;
		case SDLK_RIGHT:
			velX_ += MAX_VEL;
			break;
		case SDLK_LEFT:
			velX_ -= MAX_VEL;
			break;
		}
	}
	//If a key is released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			velY_ += MAX_VEL;
			break;
		case SDLK_DOWN:
			velY_ -= MAX_VEL;
			break;
		case SDLK_RIGHT:
			velX_ -= MAX_VEL;
			break;
		case SDLK_LEFT:
			velX_ += MAX_VEL;
			break;
		}
	}
}

void Texture::move(float timeStep)
{
	//Move the texture on the x axis
	posX_ += velX_ * timeStep;
	//If the texture went too far on the left or right side of the screen
	if (posX_ < 0) 
	{
		posX_ = 0;
	}
	else if (posX_ > SCREEN_WIDTH - width_)
	{
		posX_ = SCREEN_WIDTH - width_;
	}
	//Move the texture on the y axis
	posY_ += velY_ * timeStep;
	//If the texture went too far up or down the screen
	if (posY_ < 0) 
	{
		posY_ = 0;
	}
	else if (posY_ > SCREEN_HEIGHT - height_)
	{
		posY_ = SCREEN_HEIGHT - height_;
	}
}

