#include "Window.h"



Window::Window()
{
	window_ = NULL;
	renderer_ = NULL;
}



Window::~Window()
{
	close();
}



bool Window::init()
{
	bool success = true;
	//Create window
	window_ = SDL_CreateWindow("Game1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window_ == NULL)
	{
		cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
		success = false;
	}
	else
	{
		//Create renderer
		renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer_ == NULL)
		{
			cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
		}
	}
	return success;
}



void Window::close()
{
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	renderer_ = NULL;
	window_ = NULL;
}



SDL_Texture* Window::loadTexture(string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		cout << "Unable to load image " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << endl;
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer_, loadedSurface);
		if (newTexture == NULL)
		{
			cout << "Unable to create texture from " << path.c_str() << "! SDL Error: " << SDL_GetError() << endl;
		}
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}



SDL_Renderer* Window::getRenderer()
{
	return renderer_;
}



SDL_Window* Window::getWindow()
{
	return window_;
}