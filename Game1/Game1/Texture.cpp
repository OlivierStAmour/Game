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



Texture::Texture(string path)
{
	texture_ = NULL;

	posX_ = 0.0;
	posY_ = 0.0;

	velX_ = 0;
	velY_ = 0;

	width_ = 0;
	height_ = 0;

	path_ = path;
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



bool Texture::loadFromFile(Window* window) 
{
	//Loading success flag
	bool success = true;
	//Load PNG texture from the renderer in the window
	texture_ = window->loadTexture(path_);
	if (texture_ == NULL)
	{
		cout << "Failed to load image!" << endl;
		success = false;
	}
	return success;
}



void Texture::render(Window* window)
{	
	//Clear screen
	SDL_RenderClear(window->getRenderer());
	
	//Render texture to screen
	SDL_RenderCopy(window->getRenderer(), texture_, NULL, NULL);

	//Update screen
	SDL_RenderPresent(window->getRenderer());
}



void handleEvent(SDL_Event& e)
{


}