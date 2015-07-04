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



void Texture::setBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(texture_, blending);
}



void Texture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(texture_, alpha);
}



bool Texture::loadFromFile(Window* window, string path)
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
			texture_ = SDL_CreateTexture(window->getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);
			if (texture_ == NULL)
			{
				cout << "Unable to create blank texture! SDL Error: " << SDL_GetError() << endl;
				success = false;
			}
			else
			{
				//Set blend mode for transparent color;
				SDL_SetTextureBlendMode(texture_, SDL_BLENDMODE_BLEND);
				
				//Lock texture for manipulation
				SDL_LockTexture(texture_, NULL, &pixels_, &pitch_);

				//Copy loaded/formatted surface pixels
				memcpy(pixels_, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);

				//Get image dimensions
				width_ = formattedSurface->w;
				height_ = formattedSurface->h;
				
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
				SDL_UnlockTexture(texture_);
				pixels_ = NULL;
				
			}
			//Free old formatted surface
			SDL_FreeSurface(formattedSurface);
		}
		//Free old loaded surface
		SDL_FreeSurface(loadedSurface);
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
	//If the texture went too far on the left side of the screen
	if (posX_ < 0) 
	{
		posX_ = 0;
	}
	//If the texture went too far on the right side of the screen
	else if (posX_ > SCREEN_WIDTH - width_)
	{
		posX_ = SCREEN_WIDTH - width_;
	}
	//Move the texture on the y axis
	posY_ += velY_ * timeStep;
	//If the texture went too far up the screen
	if (posY_ < 0) 
	{
		posY_ = 0;
	}
	//If the texture went too far down the screen
	else if (posY_ > SCREEN_HEIGHT - height_)
	{
		posY_ = SCREEN_HEIGHT - height_;
	}
}



int Texture::getWidth()
{
	return width_;
}


int Texture::getHeight()
{
	return height_;
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



void* Texture::getPixels()
{
	return pixels_;
}



int Texture::getPitch()
{
	return pitch_;
}