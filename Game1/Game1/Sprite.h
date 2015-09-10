#ifndef SPRITE
#define SPRITE

#include "Texture.h"

class Sprite : public Texture
{
public:
	Sprite();
	~Sprite();
private:
	SDL_Rect clip_;
};


#endif