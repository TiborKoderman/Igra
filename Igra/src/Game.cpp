#include "Game.h"
#include "ECS/Components.h"
#include "ECS/ECS.h"
#include "Map.h"
#include "Collision.h"
#include <fstream>
#include <iterator>
#include "NPC.h"
#include "Menu.h"

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

void calculateScore(Uint64 &score);
Map* map;
Menu *menu;

bool ng = 1;

GameOver *gameover;

SDL_Renderer* Game::renderer = NULL;
std::vector<Enemy> enemies;
std::vector<Villager> villagers;

Manager manager;

auto& player(manager.addEntity());

Uint64 Score;
int Difficulty = 0, startPos = 0;
int GameRunning = 0;

SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

bool playerAlive = 1;

void saveEnteties(Uint64 &gameTimer, vector<Enemy> &enemies, vector<Villager> &villagers, Map &map, Entity &Player, int &Difficulty);
void loadEnteties(Uint64& gameTimer, vector<Enemy>& enemies, vector<Villager>& villagers, Map& map, int& Difficulty);

class SaveState
{
public:
	Uint64 gameTimer;
	int enemies;
	int villagers;

	Map map;

	Vector2D PlayerPos;
	int Difficulty;
};

/*
class GameState
{
	int state = 0;

	void SaveGame();
	void LoadGame();
};
*/

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
	menu = new Menu();
	gameover = new GameOver();
	
	needToInit = true;

	timerRect.x = 0;
	timerRect.y = 0;
	timerRect.h = 50;
	timerRect.w = 100;
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
	
	if (!GameRunning)
	{
		menu->Loop(Difficulty, startPos, GameRunning, ng);
	}
	else if (GameRunning == true)
	{
		
		if (needToInit)
		{
			if (ng)
				initEnteties();
			else
				loadEnteties(gameTimer, enemies, villagers, *map, Difficulty);
			needToInit = false;
		}
		

		for (auto& i : enemies)
			i.Update();
		for (auto& i : villagers)
			i.Update();


		static Uint32 lastSpread = SDL_GetTicks();

		manager.refresh();
		manager.update();


		for (auto cc : colliders)
			Collision::AABB(player.getComponent<ColliderComponent>(), *cc);


		if (SDL_GetTicks() - lastSpread > 1000 * (2.0f/(Difficulty+1))) {
			map->FireSpread();
			lastSpread = SDL_GetTicks();
		}


		for (int i = 0; i < 18; i++)
			for (int j = 0; j < 32; j++)
			{
				if (Collision::AABB(player.getComponent<ColliderComponent>().collider, map->map[i][j].rect))
					map->map[i][j].PutOutFire();


				for (auto& vil : villagers)
					if (Collision::AABB(vil.dest, map->map[i][j].rect))
						map->map[i][j].PutOutFire();


				map->map[i][j].TileUpdate(30000/(Difficulty+1));
			}

		for (auto& i : enemies)
		{
			if (Collision::AABB(player.getComponent<ColliderComponent>().collider, i.dest))
				playerAlive=false;
			//!TODO: Kill player, remove score
		}

		
		for (auto& j:villagers)
		{
			int del;
			bool ndel=false;
			int cnt = 0;
			for (auto& i:enemies)
			{
			if (Collision::AABB(j.dest, i.dest))
				{
				ndel = true;
				del = cnt;
				}
			cnt++;
			}
			if(ndel)
				enemies.erase(enemies.begin() + (del));
		}
		
		
		if (isGameOver() == 0 || !playerAlive)
		{
			GameRunning = -1;
			calculateScore(Score);
			cout << "Score: " << Score << "\n";
			if(gameover->Loop(Score, 0))
			{
				isRunning = false;
			}
			
		}

		if (isGameOver() == 1)
		{
			Score += pow(100,Difficulty+1) * ((1000*180) / (gameTimer + 1));
			calculateScore(Score);
			cout << "Score: " << Score << "\n";
			GameRunning = - 1;
			if (gameover->Loop(Score, 1))
			{
				isRunning = false;
			}
			
		}


		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				saveEnteties(gameTimer, enemies, villagers, *map, player, Difficulty);
				isRunning = false;
				break;

			}

		}
	}
}
void Game::render()
{

	SDL_RenderClear(renderer);
	if (!GameRunning)
		menu->Render(Difficulty, startPos);
	if (GameRunning == -1)
		gameover->render();

	if (GameRunning == 1)
		{
		map->DrawMap();
		for (auto& i : enemies)
			i.Draw();
		for (auto& i : villagers)
			i.Draw();

		TextureManager::Write(std::to_string(gameTimer / 1000), 3, timerRect, { 255,255,255 });
		manager.draw();
		}


			
		SDL_RenderPresent(renderer);
	
}

void Game::clean()
{
	needToInit = false;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	printf("Game cleaned\n");
}

int Game::isGameOver()
{
	int cnt2 = 0;
	int cnt1 = 0;
	for (int i = 0; i < 18; i++)
		for (int j = 0; j < 32; j++)
		{
			if (map->map[i][j].value == 2)
				cnt2++;
			if(map->map[i][j].value == 1)
				cnt1++;
		}
	if (((float)cnt2 / (18.0f * 32.0f)) * 100 > 77)
		return 0;
	else if (cnt1 == 0)
		return 1;
	else return -1;
}

/*
void GameState::SaveGame()
{
	std::fstream save("save.sav", std::ios::binary);
	if (save.is_open())
	{

		save.close();
	}
	

}
*/

void Game::initEnteties()
{

	gameTimer = SDL_GetTicks();

	for (int i = 0; i < 3 * Difficulty; i++)
	{
		Enemy* temp = new Enemy(Difficulty*2);
		enemies.push_back(*temp);
	}

	for (int i = 0; i < 3; i++)
	{
		villagers.push_back(*(new Villager));
	}
	Vector2D startingPosition;

	if (startPos == 0)
	{
		startingPosition.x = rand() % (1920 - 60);
		startingPosition.y = rand() % (1080 - 60);
	}

	if (startPos == 1)
	{
		startingPosition.x = 0;
		startingPosition.y = 0;
	}
	if (startPos == 2)
	{
		startingPosition.x = 1920-60;
		startingPosition.y = 0;
	}
	if (startPos == 3)
	{
		startingPosition.x = 1920-60;
		startingPosition.y = 1080-60;
	}
	if (startPos == 4)
	{
		startingPosition.x = 0;
		startingPosition.y = 1080-60;
	}

	Score = 0;

	player.addComponenet<TransformComponent>(startingPosition.x, startingPosition.y);
	player.addComponenet<SpriteComponent>("assets/player.png");
	player.addComponenet<KeyboardController>();
	player.addComponenet<ColliderComponent>("player");
}

void loadEnteties(Uint64 &gameTimer, vector<Enemy> &enemies, vector<Villager> &villagers, Map &map,  int &Difficulty)
{
	gameTimer = SDL_GetTicks();

	SaveState save;

	ifstream file("save.sav", ios::binary);
	file.read((char*)&save, sizeof(save));
	file.close();

	Vector2D PlayerPos;
	gameTimer = save.gameTimer;
	int numenemies = save.enemies;
	int numvillagers = save.villagers;
	map = save.map;
	PlayerPos = save.PlayerPos;
	Difficulty= save.Difficulty;

	for (int i = 0; i < numenemies; i++)
	{
		Enemy* temp = new Enemy(Difficulty * 2);
		enemies.push_back(*temp);
	}

	for (int i = 0; i < numvillagers; i++)
	{
		villagers.push_back(*(new Villager));
	}


	player.addComponenet<TransformComponent>(PlayerPos.x, PlayerPos.y);
	player.addComponenet<SpriteComponent>("assets/player.png");
	player.addComponenet<KeyboardController>();
	player.addComponenet<ColliderComponent>("player");
}




void saveEnteties(Uint64 &gameTimer, vector<Enemy> &enemies, vector<Villager> &villagers, Map &map, Entity &Player, int &Difficulty)
{
	SaveState save;
	Vector2D PlayerPos;

	PlayerPos.x = player.getComponent<TransformComponent>().position.x;
	PlayerPos.y = player.getComponent<TransformComponent>().position.y;

	save.gameTimer = gameTimer;
	save.enemies = enemies.size();
	save.map = map;
	save.villagers = villagers.size();
	save.PlayerPos = PlayerPos;
	save.Difficulty = Difficulty;

	ofstream file("save.sav", ios::binary);
	file.write((char*)&save, sizeof(save));
	file.close();
}



void calculateScore(Uint64 &score)
{
	//static int once;
	int cntOnFire=0;
	int cntBurnt=0;
		for (int i = 0; i < 18; i++)
			for (int j = 0; j < 32; j++)
			{
				if (map->map[i][j].value == 1)
					cntOnFire++;
				if (map->map[i][j].value == 2)
					cntBurnt++;
			}
		score += ((18 * 32) - cntOnFire) * pow(2, Difficulty);
		score += ((18 * 32) - cntBurnt) * pow(4, Difficulty);
}