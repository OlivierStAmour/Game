#include "Window.h"



Window::Window()
{
	window_ = NULL;
	renderer_ = NULL;
	camera_ = new SDL_Rect();
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
		renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
		if (renderer_ == NULL)
		{
			cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);

			//Initialize camera
			*camera_ = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
		}
	}

	return success;
}

void Window::moveCamera(float texturePositionX, float texturePositionY)
{
	//Update camera to follow the texture and keep it in the middle of the screen
	camera_->x = (texturePositionX - DOT_WIDTH / 2) - SCREEN_WIDTH / 2;
	camera_->y = (texturePositionY - DOT_HEIGHT / 2) - SCREEN_HEIGHT / 2;
	
	//Don't move the camera if it goes too far left
	if (camera_->x < 0)
	{
		camera_->x = 0;
	}
	//Don't move the camera if it goes too far up
	if (camera_->y < 0)
	{
		camera_->y = 0;
	}
	//Don't move the camera if it goes too far down
	if (camera_->y > LEVEL_HEIGHT - camera_->h)
	{
		camera_->y = LEVEL_HEIGHT - camera_->h;
	}
	//Don't move the camera if it goes too far right
	if (camera_->x > LEVEL_WIDTH - camera_->w)
	{
		camera_->x = LEVEL_WIDTH - camera_->w;
	}
}

void Window::close()
{
	delete camera_;
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	camera_ = NULL;
	renderer_ = NULL;
	window_ = NULL;
	
}


SDL_Renderer* Window::getRenderer()
{
	return renderer_;
}



SDL_Window* Window::getWindow()
{
	return window_;
}



SDL_Rect* Window::getCamera()
{
	return camera_;
}