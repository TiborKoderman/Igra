#include "NPC.h"
#include "TextureManager.h"
#include "Map.h"

Enemy::~Enemy()
{
	/*
	texture = TextureManager::LoadTexture("assets/dirt.png");
	TextureManager::Draw(texture, src, dest);
	*/
}

Enemy::Enemy(int speed)
{
	this->speed = speed;
	texture = TextureManager::LoadTexture("assets/enemy.png");

	//srand(time(NULL));

	src.x = 0;
	src.y = 0;
	src.w = dest.w = 60;
	src.h = dest.h = 60;

	dest.x = (rand() % 32) * 60;
	dest.y = (rand() % 18) * 60;

	destX = (rand() % 32) * 60;
	destY = (rand() % 18) * 60;
}





void Enemy::Update()
{
	if (SDL_GetTicks() - lastTime > 5000)
	{
		destX = (rand() % 32) * 60;
		destY = (rand() % 18) * 60;
		lastTime = SDL_GetTicks();
	}



	//dest = src;
		//dest.x += (rand()% 3-1)*60;
		//dest.y += (rand()% 3-1)*60;
	//std::cout << "x prej: " << (dest.x) << "\n";
	if (dest.x < destX)
	{
	//	std::cout << "increasing x\n";
		dest.x+=speed;
		//std::cout << &dest;
	}
	if (dest.x > destX)
	{
	//	std::cout << "decreasing x\n";
		dest.x = dest.x-=speed;
		//std::cout << &dest;
	}
	//std::cout << "x pol: " << (dest.x) << "\n";
	if (dest.y < destY)
		dest.y+=speed;
	if (dest.y > destY)
		dest.y-=speed;
	

	
	if (dest.x > (1920 - dest.w))
		dest.x = 0;
	if (dest.x < 0)
		dest.x = 1920 - dest.w;
	if (dest.y < 0)
		dest.y = 1080 - dest.h;
	if (dest.y > 1080 - dest.h)
		dest.y = 0;
	
	//std::cout << "increasing x: \n";

	
	
	//std::cout << "y: " << (dest.y) << "\n";
	
}

void Enemy::Draw()
{
	TextureManager::Draw(texture, src, dest);
	//dest.x++;
	//rect = dest;
	//std::cout << "Rendering...\n";
	
}



Villager::Villager()
{
	texture = TextureManager::LoadTexture("assets/Villager.png");

	//srand(time(NULL));

	src.x = 0;
	src.y = 0;
	src.w = dest.w = 60;
	src.h = dest.h = 60;

	dest.x = (rand() % 32) * 60;
	dest.y = (rand() % 18) * 60;

	destX = (rand() % 32) * 60;
	destY = (rand() % 18) * 60;

	lastTime = SDL_GetTicks();
}


void Villager::Draw()
{
	TextureManager::Draw(texture, src, dest);
}


void Villager::Update()
{
	if (SDL_GetTicks() - lastTime > 6000)
	{
		destX = (rand() % 32) * 60;
		destY = (rand() % 18) * 60;
		lastTime = SDL_GetTicks();
	}



	if (dest.x < destX)
		dest.x++;
	if (dest.x > destX)
		dest.x--;
	if (dest.y < destY)
		dest.y++;
	if (dest.y > destY)
		dest.y--;


	if (dest.x > (1920 - dest.w))
		dest.x = 0;
	if (dest.x < 0)
		dest.x = 1920 - dest.w;
	if (dest.y < 0)
		dest.y = 1080 - dest.h;
	if (dest.y > 1080 - dest.h)
		dest.y = 0;

}


void Villager::chaseFire(Map* map)
{


}



void Villager::UpdatePos()
{

	//std::cout << "Updating enemy position:\n";
	destX = (rand() % 32) * 60;
	destY = (rand() % 18) * 60;
}