#ifndef TEXTURE
#define TEXTURE

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>
#include <vector>
#include "Window.h"


using namespace std;



//The dimensions of the dot
static const int DOT_WIDTH = 20;
static const int DOT_HEIGHT = 20;

//The maximum velocity of the dot
static const int MAX_VEL = 640;

class Texture 
{
public:
	//Constructors
	Texture();
	Texture(float posX, float posY);

	//Deallocates memory
	~Texture();

	//Deallocates texture
	void free();

	//Loads image at specified path
	bool loadFromFile(Window* window, string path);

	//Shows the texture on the window
	void render(Window* window, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Takes the key presses and adjusts the texture's velocity
	void handleEvent(SDL_Event& e);
	
	//Moves the texture
	void move(float timeStep);

	//CheckCollision
	bool checkCollision();

	//Lock the texture (Pixel manipulation available)
	bool lockTexture();

	//Unlock the texture (Pixel manipulation not available)
	bool unlockTexture();

	//Add a collision box to check
	void addCollisionBox(SDL_Rect* collisionBox);

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Access to dimensions
	int getWidth();
	int getHeight();

	//Access to collisionBox
	SDL_Rect* getCollisionBox();

	//Access to the pixels of the texture
	void* getPixels();

	//Access to the pitch of the texture
	int getPitch();

private:
	
	//Collision box of the texture
	SDL_Rect* collisionBox_;

	//Collision boxes the texture has to check for
	vector<SDL_Rect*> collisionBoxesToCheck_;

	//The hardware texture
	SDL_Texture* texture_;
	void* pixels_;
	int pitch_;

	//Position of the texture on the x and y axis 
	float posX_, posY_;
	//Velocity of the texture on the x and y axis
	float velX_, velY_;

	//Image dimensions
	int width_;
	int height_;

	//Image path
	string path_;
};


#endif

