#include <Texture.h>



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
	SDL_Rect renderQuad = { posX_, posY_, width_, height_};

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Initialize renderer color
	SDL_SetRenderDrawColor(window->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);

	//Clear screen
	SDL_RenderClear(window->getRenderer());
	
	//Render texture to screen
	SDL_RenderCopyEx(window->getRenderer(), texture_, clip, &renderQuad, angle, center, flip);

	//Update screen
	SDL_RenderPresent(window->getRenderer());
}



void handleEvent(SDL_Event& e)
{


}