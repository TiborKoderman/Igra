#include "NPC.h"
#include "TextureManager.h"
#include "Map.h"
#include "Collision.h"

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

	lockedOn = false;
}


void Villager::Draw()
{
	TextureManager::Draw(texture, src, dest);
}


void Villager::Update(Map map, std::vector<Enemy> enemies)
{
	if (SDL_GetTicks() - lastTime > 6000 && !lockedOn)
	{
		destX = (rand() % 32) * 60;
		destY = (rand() % 18) * 60;
		lastTime = SDL_GetTicks();
	}


	nqx = dest.x / 60;
	nqy = dest.y / 60;

	

	for(int i = -2; i<=2;i++)
		for (int j = -2; j <= 2; j++)
		{
			dpx = i+nqx;
			dpy = j+nqy;
			if (dpx + i < 0)
				dpx = 0;
			else if (dpx + i > 31)
				dpx = 31;
			if (dpy + j < 0)
				dpy = 0;
			else if (dpy + j > 17)
				dpy = 17;
			
			for (auto& i : enemies)
			{
				SDL_Rect lockBox;
				lockBox.x = dpx;
				lockBox.y = dpy;
				lockBox.w = 5 * 60;
				lockBox.h = 5 * 60;
				if (Collision::AABB(lockBox, i.dest))
				{
					destX = i.dest.x;
					destY = i.dest.y;
					lockedOn = true;
					break;
				}
			}
			if (map.map[dpy][dpx].value == 1)
			{
				destX = (dpx)*60;
				destY = (dpy)*60;
				lockedOn = true;
				break;
			}
			else
			{
				lockedOn = false;
			}
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