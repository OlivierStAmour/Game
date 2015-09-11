#ifndef SPRITESHEET
#define SPRITESHEET

#include "Texture.h"
#include "Sprite.h"

const int N_MAX_CLIPS = 10;

class SpriteSheet : public Texture
{

public:
	SpriteSheet();
	SpriteSheet(Window* window, float posX, float posY);

	void generateClips();
	void destroyClips();

	void setStandBySpriteClip(int clip, int posX, int posY, int w, int h);


private:
	SDL_Rect* standBySpriteClips_[N_MAX_CLIPS];
	SDL_Rect* moveSpriteClips_[N_MAX_CLIPS];
	SDL_Rect* jumpSpriteClips_[N_MAX_CLIPS];
	SDL_Rect* attackSpriteClips_[N_MAX_CLIPS];
};
#endif