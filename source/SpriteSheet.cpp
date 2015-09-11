#include "SpriteSheet.h"


SpriteSheet::SpriteSheet()
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



SpriteSheet::SpriteSheet(Window* window, float posX, float posY)
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


void SpriteSheet::generateClips()
{
	for (int i = 0; i < N_MAX_CLIPS; i++)
	{
		standBySpriteClips_[i] = new SDL_Rect();
		moveSpriteClips_[i] = new SDL_Rect();
		jumpSpriteClips_[i] = new SDL_Rect();
		attackSpriteClips_[i] = new SDL_Rect();
	}
}


void SpriteSheet::destroyClips()
{
	for (int i = 0; i < N_MAX_CLIPS; i++)
	{
		if (standBySpriteClips_[i] != 0)
		{
			delete standBySpriteClips_[i];
			standBySpriteClips_[i] = 0;
		}

		if (moveSpriteClips_[i] != 0)
		{
			delete moveSpriteClips_[i];
			moveSpriteClips_[i] = 0;
		}

		if (jumpSpriteClips_[i] != 0)
		{
			delete jumpSpriteClips_[i];
			jumpSpriteClips_[i] = 0;
		}

		if (attackSpriteClips_[i] != 0)
		{
			delete attackSpriteClips_[i];
			attackSpriteClips_[i] = 0;
		}
	}
}


void SpriteSheet::setStandBySpriteClip(int clip, int posX, int posY, int w, int h)
{
	standBySpriteClips_[clip]->x = posX;
	standBySpriteClips_[clip]->y = posY;
	standBySpriteClips_[clip]->w = w;
	standBySpriteClips_[clip]->h = h;
}