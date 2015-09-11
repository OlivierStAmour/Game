#ifndef CHARACTER
#define CHARACTER

#include "sprite_sheet.h"

class Character
{
public:
	Character();
	Character(Window* window, float posX, float posY);
	~Character();

	void render();

	SpriteSheet* getSpriteSheet();

private:
	SpriteSheet* spriteSheet_;
	SDL_Rect* currentSprite_;
};

#endif
