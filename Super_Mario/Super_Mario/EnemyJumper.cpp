#include "EnemyJumper.h"



EnemyJumper::EnemyJumper()
{
}


EnemyJumper::~EnemyJumper()
{
}

void EnemyJumper::Set(Texture &image, int x, int y)
{
	sprite.setTexture(image);
	rect = FloatRect(x, y, 16, 16);
	rectJ = FloatRect(x - 32, y - 64, 80, 96);
	onGround = true;
	dy = 0.05;
	currentFrame = 0;
	active = false;
}

void EnemyJumper::Update(float time, bool pLife, String *TileMap, float *offsetX, float *offsetY)
{
	if (intersect)
		if (active)
		{
			if (rect.top >= 128 && onGround)
			{
				rect.top += -0.70;
			}
			if (rect.top < 128)
				onGround = false;
			if (!onGround)
			{
				rect.top += +0.70;
			}
			if (rect.top == 208)
				onGround = true;
			Collision(TileMap);
			sprite.setTextureRect(IntRect(50, 15, 30, 24));
		}
	if (!active)
	{
		if (rect.top != 208)
			onGround = false;
		if (!onGround)
		{
			rect.top += +0.70;
		}
		if (rect.top == 208)
			onGround = true;
		sprite.setTextureRect(IntRect(20, 10, 24, 16));

		Collision(TileMap);

	}
	sprite.setPosition(rect.left - *offsetX, rect.top - *offsetY);
}


void EnemyJumper::Collision(String *TileMap)
{
	for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
		for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
			if ((TileMap[i][j] == 'P') || (TileMap[i][j] == 'b') || (TileMap[i][j] == 'k') || (TileMap[i][j] == '0') || (TileMap[i][j] == 'r') || (TileMap[i][j] == 't'))
			{
				if (dy > 0) rect.top = i * 16 - rect.height;
				else if (dy < 0) rect.top = i * 30 + 16;
			}
}
