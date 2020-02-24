#include "Map.h"
#include "TextureManager.h"


Map::Map()
{
	treeBurnt = TextureManager::LoadTexture("assets/treeBurnt.png");
	treeOnFire = TextureManager::LoadTexture("assets/treeOnFire.png");
	tree = TextureManager::LoadTexture("assets/tree.png");

	for (int i = 0; i < 10; i++)
		lvl1[rand() % 27][rand() % 48] = 1;

	LoadMap(lvl1);
	src.x = src.y = 0;
	src.w = dest.w = 40;
	src.h = dest.h = 40;

	dest.x = dest.y = 0;
}

Map::~Map()
{
	SDL_DestroyTexture(tree);
	SDL_DestroyTexture(treeOnFire);
}

void Map::LoadMap(int arr[27][48])
{
	for (int row = 0; row < 27; row++)
	{
		for (int column = 0; column < 48; column++)
		{
			map[row][column].value = arr[row][column];
			map[row][column].rect.x = column * 40;
			map[row][column].rect.y = row * 40;
			map[row][column].rect.h = 40;
			map[row][column].rect.w = 40;
		}
	}
}

void Map::DrawMap()
{
	int type = 0;

	for (int row = 0; row < 27; row++)
	{
		for (int column = 0; column < 48; column++)
		{
			type = map[row][column].value;

			dest.x = column * 40;
			dest.y = row * 40;

			switch (type)
			{
			case 0:
				TextureManager::Draw(tree, src, dest);
				break;
			case 1:
				TextureManager::Draw(treeOnFire, src, dest);
				break;
			case 2:
				TextureManager::Draw(treeBurnt, src, dest);
				break;
			default:
				break;

			}

		}
	}
}

void Map::FireSpread()
{
	int x, y;

	for (int i = 0; i < 27;i++)
		for (int j = 0; j < 48; j++)
		{
			if (map[i][j].value == 1 && 60 <= rand() % 100 && i!= 0 &&j!=0&&i!=26&&j!=47)
			{
				x = i + rand() % 3 - 1;
				y = j + rand() % 3 - 1;
				if(map[x][y].value == 0)
					map[x][y].SetOnFire();
			}
		}
}
