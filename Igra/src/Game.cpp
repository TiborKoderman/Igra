#include "Game.h"
#include "Vector2D.h"
#include "ECS/Components.h"
#include "ECS/ECS.h"
#include "Map.h"
#include "Collision.h"
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
auto& wall(manager.addEntity());

SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());


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



	
	player.addComponenet<TransformComponent>(2);
	player.addComponenet<SpriteComponent>("assets/player.png");
	player.addComponenet<KeyboardController>();
	player.addComponenet<ColliderComponent>("player");

	wall.addComponenet<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponenet<SpriteComponent>("assets/dirt.png");
	wall.addComponenet<ColliderComponent>("wall");
	
	tile0.addComponenet<TileComponent>(200, 200, 32, 32, 0);
	tile1.addComponenet<TileComponent>(250, 250, 32, 32, 1);
	tile1.addComponenet<ColliderComponent>("dirt");
	tile2.addComponenet<TileComponent>(150, 150, 32, 32, 2);
	tile2.addComponenet<ColliderComponent>("grass");
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
	

	for (auto cc : colliders)
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
	
	


	if (SDL_GetTicks() - lastSpread > 3000) {
		map->FireSpread();
		map->LoadMap(map->map);
		lastSpread = SDL_GetTicks();
	}
}
void Game::render()
{
	SDL_RenderClear(renderer);
	//map->DrawMap();
	
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

