#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Map.h"
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <list>
#include <SDL_ttf.h>

class ColliderComponent;


#define WindowWidth 1920
#define WindowHeight 1080


class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	int score;

	void handleEvents();
	void update();
	void render();
	void clean();
	int isGameOver();
	bool running() { return isRunning; };
	void SaveGame();

	static SDL_Renderer *renderer;
	static SDL_Event event;

	SDL_Rect timerRect;

	Uint64 gameTimer;

	//Menu menu;

	void initEnteties();
	//void loadEnteties(Uint64 gameTimer, std::vector<Enemy> enemies, std::vector<Villager> villagers, Map map, Entity Player, Vector2D PlayerPos, int Difficulty);
	//void saveEnteties(Uint64 gameTimer, std::vector<Enemy> enemies, std::vector<Villager> villagers, Map map, Entity Player, Vector2D PlayerPos, int Difficulty);
	int needToInit;

	static std::vector<ColliderComponent*> colliders;
private:
	
	int cnt = 0;
	bool isRunning;
	SDL_Window* window;
};

/*
class SaveState
{
public:
	Uint64 gameTimer;
	std::vector<Enemy> enemies;
	std::vector<Villager> villagers;

	Map map;

	Entity player;

	void load();
	void save(Uint64 gameTimer, std::vector<Enemy> enemies, vector<Villager> villagers, Map map, Entity Player, Vector2D PlayerPos, int Difficulty);
};*/