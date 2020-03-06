#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::Sprite(SDL_Renderer* renderer, const char* filename, int sizeX, int sizeY)
{
	pSpriteTex = IMG_LoadTexture(renderer, filename);

	SDL_QueryTexture(pSpriteTex, NULL, NULL, &src.w, &src.h);

	src.x = 0;
	src.y = 0;

	dst.x = 0;
	dst.y = 0;
	dst.w = sizeX;
	dst.h = sizeY;
}

Sprite::~Sprite()
{
}

void Sprite::cleanup()
{
	SDL_DestroyTexture(pSpriteTex);
}

void Sprite::setPosition(int x, int y)
{
	dst.x = x;// -dst.w * 0.5f;
	dst.y = y;// -dst.h * 0.5f;
}

SDL_Rect Sprite::getPosition()
{
	return dst;
}

void Sprite::setSize(int x, int y)
{
	dst.w = x;
	dst.h = y;
}

void Sprite::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, pSpriteTex, &src, &dst);
}
