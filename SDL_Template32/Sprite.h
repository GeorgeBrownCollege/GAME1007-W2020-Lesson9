#pragma once
#include<SDL_image.h>

// Sprite class which contains a texture, position, velocity, size, and functions for drawing it.

class Sprite
{
private:
	SDL_Texture* pSpriteTex = nullptr;
	SDL_Rect src;

public:
	SDL_Rect dst;

	// velocity (maybe not necessary for every sprite)
	float velX = 0;
	float velY = 0;

	// constructors -- these are used when initializing an object
	Sprite();
	Sprite(SDL_Renderer* renderer, const char* filename, int sizeX, int sizeY);
	
	// destructor -- used when the object is to be removed from memory
	~Sprite();

	void setPosition(int x, int y);
	SDL_Rect getPosition();

	
	void setSize(int x, int y);
	void draw(SDL_Renderer* renderer);

	void cleanup();
};

