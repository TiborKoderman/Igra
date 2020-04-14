#include "TextureManager.h"
#include "Game.h"


SDL_Texture* TextureManager::LoadTexture(const char* texture)
{
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}


void TextureManager::Write(std::string text, int size, SDL_Rect rect, SDL_Color color)
{
	TTF_Font* Sans = TTF_OpenFont("Sans.ttf", size);
	SDL_Surface* textSurface = TTF_RenderText_Solid(Sans, text.c_str(), color);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
	SDL_RenderCopy(Game::renderer, Message, NULL, &rect);
	SDL_FreeSurface(textSurface);
}
void TextureManager::Write(std::string text, int size, SDL_Rect rect)
{
	TTF_Font* Sans = TTF_OpenFont("Sans.ttf", size);
	SDL_Surface* textSurface = TTF_RenderText_Solid(Sans, text.c_str(), { 255,255,255 });
	SDL_Texture* Message = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
	SDL_RenderCopy(Game::renderer, Message, NULL, &rect);
	SDL_FreeSurface(textSurface);
}

