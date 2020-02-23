#pragma once
#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"
#include <string>

class TileComponent : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	int tileID;
	std::string path;


	TileComponent() = default;

	TileComponent(int x, int y, int w, int h, int id)
	{
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;

		switch (tileID)
		{
		case 0:
			path = "assets/tree.png";
			break;
		case 1:
			path = "assets/treeOnFire.png";
			break;
		case 2:
			path = "assets/grass.png";
			break;
		}

	}

	void init() override
	{
		entity->addComponenet<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponenet<SpriteComponent>(path.c_str());
		sprite = &entity->getComponent<SpriteComponent>();
	}







};