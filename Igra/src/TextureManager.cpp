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


void TextureManager::Write(std::string text, int size, SDL_Rect rect)
{
	SDL_Color White = { 255,255,255 };
	TTF_Font* Sans = TTF_OpenFont("assets/comic.ttf", size);
	SDL_Surface* textSurface = TTF_RenderText_Solid(Sans, text.c_str(), White);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
	SDL_RenderCopy(Game::renderer, Message, NULL, &rect);
	SDL_FreeSurface(textSurface);
}

void TextureManager::Write(std::string text, SDL_Rect rect)
{
	SDL_Color White = { 255,255,255 };
	TTF_Font* Sans = TTF_OpenFont("assets/comic.ttf", rect.h);
	SDL_Surface* textSurface = TTF_RenderText_Solid(Sans, text.c_str(), White);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
	SDL_RenderCopy(Game::renderer, Message, NULL, &rect);
	SDL_FreeSurface(textSurface);
}

void TextureManager::Write(std::string text, int x, int y, int w, int h)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_Color White = { 255,255,255 };
	TTF_Font* Sans = TTF_OpenFont("assets/comic.ttf", rect.h);
	SDL_Surface* textSurface = TTF_RenderText_Solid(Sans, text.c_str(), White);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
	SDL_RenderCopy(Game::renderer, Message, NULL, &rect);
	SDL_FreeSurface(textSurface);
}


void TextureManager::Write(std::string text, int size, SDL_Rect rect, SDL_Color color)
{
	TTF_Font* Sans = TTF_OpenFont("assets/comic.ttf", size);
	SDL_Color White = { 255,255,255 };
	SDL_Surface* textSurface = TTF_RenderText_Solid(Sans, text.c_str(), color);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
	SDL_RenderCopy(Game::renderer, Message, NULL, &rect);
	SDL_FreeSurface(textSurface);
}

