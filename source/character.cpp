#include "character.h"
#include "sprite_sheet.h"

Character::Character()
{
	spriteSheet_ = new SpriteSheet();
}



Character::Character(Window* window, float posX, float posY)
{
	spriteSheet_ = new SpriteSheet(window, posX, posY);
}



SpriteSheet* Character::getSpriteSheet()
{
	return spriteSheet_;
}


void Character::render()
{
	spriteSheet_->render(currentSprite_);
}
