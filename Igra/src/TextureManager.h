#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>
class TextureManager
{
private:
	SDL_Color White = { 255,255,255 };

public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
	static void Write(std::string text, int size, SDL_Rect rect, SDL_Color color);
	static void Write(std::string text, int size, SDL_Rect rect);
};
