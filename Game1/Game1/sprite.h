#ifndef SPRITE
#define SPRITE

#include "texture.h"

class Sprite : public Texture
{
public:
	Sprite();
	~Sprite();
private:
	SDL_Rect clip_;
};


#endif
