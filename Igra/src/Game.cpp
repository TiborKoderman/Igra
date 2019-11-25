#include "Game.h"
SDL_Texture* playerTex, *enemyTex;

SDL_Rect srcR, destR;
SDL_Rect EnemyR;

Uint32 currentTime;
int timeSinceMove;
struct Pos
{
	int x, y;
	struct Pos* next, *prev;
}*startPos = NULL, *endPos, *c =startPos;

void fillList();
void moveEnemy();

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
		for (int i = 0; i < rand() % 90 + 10; i++)
			fillList();

		//destR.x = 0;
		//destR.x = 0;
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	playerTex = TextureManager::LoadTexture("assets/player.png", renderer);
	destR.h = WindowHeight/20;
	destR.w = WindowWidth/20;
	enemyTex = TextureManager::LoadTexture("assets/Enemy Ms.png", renderer);
	EnemyR.h = WindowHeight/20;
	EnemyR.w = WindowWidth/20;


	currentTime = SDL_GetTicks()+1000;

	moveEnemy();
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) 
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
			case SDLK_w:
				destR.y -= WindowHeight/20;
				printf("pressed w\n");
				break;
			case SDLK_s:
				destR.y += WindowHeight/20;
				printf("pressed s\n");
				break;
			case SDLK_a:
				destR.x -= WindowWidth/20;
				printf("pressed a\n");
				break;
			case SDLK_d:
				destR.x += WindowWidth/20;
				printf("pressed d\n");
				break;
			case SDLK_F11:
				if (SDL_GetWindowFlags(window) == SDL_WINDOW_FULLSCREEN)
					SDL_SetWindowFullscreen(window, false);
				else
					SDL_SetWindowFullscreen(window, true);

		}
		break;
	}
}

void Game::update()
{
	cnt++;
	if (destR.x > WindowWidth-WindowWidth/20)
		destR.x = 0;
	if (destR.x < 0)
		destR.x = WindowWidth-WindowWidth/20;
	if (destR.y > WindowWidth-WindowWidth/20)
		destR.y = 0;
	if (destR.y < 0)
		destR.y = WindowWidth-WindowWidth/20;

	moveEnemy();
	


	if (1000 < SDL_GetTicks() - currentTime)
	{
		c = c->next;
		currentTime = SDL_GetTicks();
	}
	

}
void Game::render()
{
	SDL_RenderClear(renderer);
	//stuff to render
	SDL_RenderCopy(renderer, playerTex, NULL, &destR);
	SDL_RenderCopy(renderer, enemyTex, NULL, &EnemyR);

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	printf("Game cleaned\n");
}


void fillList()
{
	struct Pos* tmp = new Pos;
	tmp->x = rand() % 20;
	tmp->y = rand() % 20;


	if (startPos == NULL)
	{
		tmp->prev = NULL;
		tmp->next = NULL;
		startPos = tmp;
		endPos = tmp;
		startPos->next = endPos;
		endPos->prev = startPos;
		
	}
	else
	{
		tmp->next = startPos;
		startPos = tmp;
		endPos->next = tmp;
		tmp->prev = endPos;
	}
	c = startPos;
}

void moveEnemy()
{
	if (c->x + EnemyR.x < c->next->x * WindowWidth/20)
		EnemyR.x += WindowWidth/80;
	if (c->x + EnemyR.x - WindowWidth / 80 > c->next->x * WindowWidth / 20)
		EnemyR.x -= WindowWidth / 80;
	if (c->y + EnemyR.y < c->next->y * WindowHeight / 20)
		EnemyR.y += WindowHeight / 80;
	if (c->y + EnemyR.y - WindowHeight / 80 > c->next->y * WindowHeight / 20)
		EnemyR.y -= WindowHeight / 80;
}
