#include "Game.h"
#include "Vector2D.h"
#include "ECS/Components.h"
#include "ECS/ECS.h"
#include "Map.h"
Uint32 currentTime;
int timeSinceMove;
/*
struct Pos
{
	int x, y;
	struct Pos* next, *prev;
}*startPos = NULL, *endPos, *c =startPos;
*/
//void fillList();
//void moveEnemy();


Map* map;

SDL_Renderer* Game::renderer = NULL;

Manager manager;
auto& player(manager.addEntity());

SDL_Event Game::event;

SDL_Rect intersect;

Game::Game()
{
}
Game::~Game()
{
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if(fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		printf("Subsystems Initialised!\n");
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			printf("Window created!\n");
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 138, 242, 164, 255);
			printf("Renderer created!\n");
		}

		srand(time(NULL));

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	map = new Map();



	
	player.addComponenet<TransformComponent>();
	player.addComponenet<SpriteComponent>("assets/player.png");
	player.addComponenet<KeyboardController>();

	player.getComponent<SpriteComponent>().destRect;

}

void Game::handleEvents()
{
	
	SDL_PollEvent(&event);
	switch (event.type) 
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	}
}

void Game::update()
{
	static Uint32 lastSpread = SDL_GetTicks();
	manager.refresh();
	manager.update();
	
	
	


	if (SDL_GetTicks() - lastSpread > 3000) {
		map->FireSpread();
		map->LoadMap(map->map);
		lastSpread = SDL_GetTicks();
	}
}
void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();
	
	manager.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	printf("Game cleaned\n");
}

