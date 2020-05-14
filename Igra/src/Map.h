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
		const int timer = SDL_GetTicks();
	}

	void TileUpdate(int interval)
	{		
		if (SDL_GetTicks() - timer > interval && value == 1)
			value = 2;
	}

	void ResetTimer()
	{
		timer = SDL_GetTicks();
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

	Tile operator=(Tile a)
	{
		value = a.value;
		rect = a.rect;
		timer = a.timer;

		return a;
	}

};



class Map
{
public:

	Map();
	~Map();

	void LoadMap(int arr[18][32]);
	void DrawMap();
	void FireSpread();

	int lvl1[18][32];

	Tile map[18][32];
	SDL_Rect src, dest;
	void Extinguish(const SDL_Rect& player);

	Map operator=(Map a)
	{
		for(int i = 0; i<18;i++)
			for (int j = 0; j < 32; j++)
			{
				lvl1[i][j] =a.lvl1[i][j];
				map[i][j] = a.map[i][j];
			}
				
		src = a.src;
		dest = a.dest;
		return a;
	}


private:

	
	SDL_Texture* treeBurnt;
	SDL_Texture* treeOnFire;
	SDL_Texture* tree;

	

};