#pragma once
#include "../Vector2D.h"
#include "Components.h"
class TransformComponent : public Component
{
public:

	Vector2D position;
	Vector2D velocity;

	int height = 60;
	int width = 60;
	int scale = 1;

	

	int speed = 5;

	TransformComponent()
	{
		position.Zero();
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(int sc)
	{
		position.Zero();
		scale = sc;
	}

	TransformComponent(float x, float y, int h, int w, int sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override
	{
		velocity.Zero();
	}

	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;

		if (position.x > (1920 - width))
			position.x = 0;
		if (position.x < 0)
			position.x = 1920 - width;
		if (position.y < 0)
			position.y = 1080 - height;
		if (position.y > (1080 - height))
			position.y = 0;
	}

};