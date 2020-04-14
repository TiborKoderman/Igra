#pragma once
#include "Game.h"

/*
class NPC
{
public:
	SDL_Rect src, dest;

	SDL_Texture* texture;

	int hp;

	NPC();
	~NPC();

	virtual void Update() = 0;
	virtual void Render();

};

class Villager
{
	SDL_Rect rect;

	SDL_Texture* texture;

	int hp;

	Villager();
	~Villager();

	void Update();
	void Render();
};
*/

class Enemy
{

	SDL_Texture* texture;

	int lastTime;
	


public:

	SDL_Rect src, dest;

	int speed;

	Enemy(int speed);
	~Enemy();

	int destX, destY;

	void Update();
	void Draw();
};

class Villager
{

	SDL_Texture* texture;

	int lastTime;



public:

	SDL_Rect src, dest;


	Villager();
	//~Villager();

	int destX, destY;
	void UpdatePos();
	void chaseFire(Map* map);

	void Update();
	void Draw();

};