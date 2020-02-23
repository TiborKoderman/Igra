#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Map.h"
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

class ColliderComponent;


#define WindowWidth 1920
#define WindowHeight 1080


class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; };
	static SDL_Renderer *renderer;
	static SDL_Event event;

	static void AddTile(int id, int x, int y);

	static std::vector<ColliderComponent*> colliders;
private:
	
	int cnt = 0;
	bool isRunning;
	SDL_Window* window;
};