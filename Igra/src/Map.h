#pragma once
#include "Game.h"

class Tile
{
public:
	int value;
	SDL_Rect rect;

	uint16_t timer;

	Tile()
	{
		timer = SDL_GetTicks();
	}

	void TileUpdate()
	{
		if (SDL_GetTicks() - timer > 30000 && value == 1)
			value = 2;
	}

	void SetOnFire()
	{
			value = 1;
			timer = SDL_GetTicks();
	}

	void PutOutFire()
	{
		if(value == 1)
			value = 0;
	}


};



class Map
{
public:

	Map();
	~Map();

	void LoadMap(int arr[27][48]);
	void DrawMap();
	void FireSpread();

	int lvl1[27][48];

	Tile map[27][48];
	SDL_Rect src, dest;
	void Extinguish(const SDL_Rect& player);
private:

	
	SDL_Texture* treeBurnt;
	SDL_Texture* treeOnFire;
	SDL_Texture* tree;

	


};