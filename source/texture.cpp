#include "texture.h"



Texture::Texture()
{
	window_ = 0;
	
	texture_ = NULL;
	collisionBox_ = NULL;

	posX_ = 0.0;
	posY_ = 0.0;

	velX_ = 0;
	velY_ = 0;

	width_ = 0;
	height_ = 0;

	path_ = "";
}



Texture::Texture(Window* window, float posX, float posY) : window_(window)
{
	window_ = window;
	
	texture_ = NULL;
	collisionBox_ = NULL;

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
	//Free the hardware texture
	if (texture_ != NULL)
	{
		SDL_DestroyTexture(texture_);
		texture_ = NULL;
	}
	//Free the collision box pointer
	if (collisionBox_ != NULL)
	{
		delete collisionBox_;
		collisionBox_ = NULL;
	}

	window_ = NULL;

	posX_ = 0.0;
	posY_ = 0.0;
	velX_ = 0;
	velY_ = 0;
	width_ = 0;
	height_ = 0;
}



bool Texture::loadFromFile(string path)
{
	//Loading success flag
	bool success = true;

	path_ = path;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	
	if (loadedSurface == NULL)
	{
		cout << "Unable to load image " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << endl;
		success = false;
	}
	else
	{
		//Convert surface to display format
		SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_RGBA8888, NULL);

		if (formattedSurface == NULL)
		{
			cout << "Unable to convert loaded surface to display format! SDL Error: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			//Create blank streamable texture
			texture_ = SDL_CreateTexture(window_->getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);
			if (texture_ == NULL)
			{
				cout << "Unable to create blank texture! SDL Error: " << SDL_GetError() << endl;
				success = false;
			}
			else
			{
				//Set blend mode to enable transparent color;
				SDL_SetTextureBlendMode(texture_, SDL_BLENDMODE_BLEND);
				
				//Lock texture for manipulation
				lockTexture();

				//Copy loaded/formatted surface pixels
				memcpy(pixels_, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);

				//Unlock texture to update
				unlockTexture();

				//Get image dimensions
				width_ = formattedSurface->w;
				height_ = formattedSurface->h;

				//Create the collision box
				collisionBox_ = new SDL_Rect();
				collisionBox_->x = int(posX_);
				collisionBox_->y = int(posY_);
				collisionBox_->h = height_;
				collisionBox_->w = width_;
			}
			//Free old formatted surface
			SDL_FreeSurface(formattedSurface);
		}
		//Free old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return success;
}

void Texture::makeBackgroundTransparent()
{
	//Get the formatted surface from the window
	SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(SDL_GetWindowSurface(window_->getWindow()), SDL_PIXELFORMAT_RGBA8888, NULL);

	//Lock texture for pixel manipulation
	lockTexture();

	//Get pixel data in editable format 
	//pitch_ / 4 because there are 4 bytes / pixel (32 bits RGBA format)
	int pixelCount = (pitch_ / 4) * height_;

	//Get the colorkey for the first pixel (most likely the background color)
	Uint32 colorKey = ((Uint32*)pixels_)[0];

	//The color key for a transparent color
	Uint32 transparent = SDL_MapRGBA(formattedSurface->format, 0xFF, 0xFF, 0xFF, 0x00);

	//Make every background pixel transparent
	for (int i = 0; i < pixelCount; i++)
	{
		if (((Uint32*)pixels_)[i] == colorKey)
		{
			((Uint32*)pixels_)[i] = transparent;
		}
	}
	//Unlock texture to update
	unlockTexture();

	//Free old formatted surface
	SDL_FreeSurface(formattedSurface);
}


void Texture::render(SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{	
	//The relative position of the texture to the camera
	int relPosX = posX_ - window_->getCamera()->x;
	int relPosY = posY_ - window_->getCamera()->y;
	
	//Renderquad using 
	SDL_Rect renderQuad = {relPosX, relPosY, (int)width_, (int)height_};
	
	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render texture to screen
	SDL_RenderCopyEx(window_->getRenderer(), texture_, clip, &renderQuad, angle, center, flip);
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
	//Declare a variable for the displacement
	float deltaX = velX_ * timeStep;
	//Move the texture on the x axis
	posX_ += deltaX;
	collisionBox_->x = (int)posX_;
	//If the texture went too far on the left side of the screen
	if (posX_ < 0) 
	{
		posX_ -= deltaX;
		collisionBox_->x = (int)posX_;
	}
	//If the texture went too far on the right side of the screen
	else if (posX_ > LEVEL_WIDTH - width_ || checkCollision())
	{
		posX_ -= deltaX;
		collisionBox_->x = (int)posX_;
	}
	//Declare a variable for the displacement
	float deltaY = velY_ * timeStep;
	//Move the texture on the y axis
	posY_ += deltaY;
	collisionBox_->y = (int)posY_;
	//If the texture went too far up the screen
	if (posY_ < 0) 
	{
		posY_ -= deltaY;
		collisionBox_->y = (int)posY_;
	}
	//If the texture went too far down the screen
	else if (posY_ > LEVEL_HEIGHT - height_ || checkCollision())
	{
		posY_ -= deltaY;
		collisionBox_->y = (int)posY_;
	}
	//Move the camera
	window_->moveCamera(posX_, posY_);
}



bool Texture::checkCollision()
{
	for (unsigned int i = 0; i < collisionBoxesToCheck_.size(); i++)
	{

		int leftA = collisionBoxesToCheck_[i]->x;
		int rightA = collisionBoxesToCheck_[i]->x + collisionBoxesToCheck_[i]->w;
		int upA = collisionBoxesToCheck_[i]->y;
		int downA = collisionBoxesToCheck_[i]->y + collisionBoxesToCheck_[i]->h;

		int leftB = collisionBox_->x;
		int rightB = collisionBox_->x + collisionBox_->w;
		int upB = collisionBox_->y;
		int downB = collisionBox_->y + collisionBox_->h;

		//Check right side for collision
		if (rightB <= leftA)
		{
			return false;
		}
		//Check left side for collision
		if (rightA <= leftB)
		{
			return false;
		}
		//Check up side for collision
		if (upB >= downA)
		{
			return false;
		}
		//Checker down side for collision
		if (upA >= downB)
		{
			return false;
		}
	}
	if (collisionBoxesToCheck_.empty())
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Texture::lockTexture()
{
	bool success = true;
	//Texture is already locked
	if (pixels_ != NULL)
	{
		cout << "Texture is already locked!" << endl;
	}
	//Lock texture
	else
	{
		if (SDL_LockTexture(texture_, NULL, &pixels_, &pitch_) != 0)
		{
			cout << "Unable to lock texture! " << SDL_GetError();
		}
	}
	return success;
}



bool Texture::unlockTexture()
{
	bool success = true;
	//Texture is not locked
	if (pixels_ == NULL)
	{
		cout << "Texture is not locked !" << endl;
	}
	//Unlock texture
	else
	{
		SDL_UnlockTexture(texture_);
		pixels_ = NULL;
		pitch_ = 0;
	}
	return success;
}



void Texture::addCollisionBox(SDL_Rect* collisionBox)
{
	collisionBoxesToCheck_.push_back(collisionBox);
}



//TODO
void setColor(Uint8 red, Uint8 green, Uint8 blue)
{

}



void Texture::setBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(texture_, blending);
}



void Texture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(texture_, alpha);
}



int Texture::getWidth()
{
	return width_;
}



int Texture::getHeight()
{
	return height_;
}



SDL_Rect* Texture::getCollisionBox()
{
	return collisionBox_;
}



void* Texture::getPixels()
{
	return pixels_;
}



int Texture::getPitch()
{
	return pitch_;
}
