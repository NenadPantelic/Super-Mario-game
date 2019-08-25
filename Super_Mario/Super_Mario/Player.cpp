#include "Player.h"

Player::Player()
{
}


Player::~Player()
{
}

void Player::Update(float time, String *TileMap, float *offsetX, float *offsetY, unsigned int *points)
{
	finish = false;
	rect.left += dx * time;
	Collision(0, TileMap, points);
	if (!onGround) dy = dy + 0.0005*time;
	rect.top += dy * time;
	onGround = false;
	Collision(1, TileMap, points);

	currentFrame += time * 0.005;
	if (currentFrame > 3) currentFrame -= 3;


	if (dx > 0) sprite.setTextureRect(IntRect(0 + 31 * int(currentFrame), 3, 16, 16));
	if (dx < 0) sprite.setTextureRect(IntRect(0 + 31 * int(currentFrame) + 16, 3, -16, 16));

	sprite.setPosition(rect.left - *offsetX, rect.top - *offsetY);
	dx = 0;

}


void Player::Collision(int num, String *TileMap, unsigned int *points)
{
	for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
		for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
		{
			if ((TileMap[i][j] == 'P') || (TileMap[i][j] == 'a') || (TileMap[i][j] == 'b') || (TileMap[i][j] == 'k') || (TileMap[i][j] == '0') || (TileMap[i][j] == 'r') || (TileMap[i][j] == 't'))
			{
				if (dy > 0 && num == 1)
				{
					rect.top = i * 16 - rect.height;  dy = 0;   onGround = true;
				}
				if (dy < 0 && num == 1)
				{
					rect.top = i * 16 + 16;   dy = 0;
				}
				if (dx > 0 && num == 0)
				{
					rect.left = j * 16 - rect.width;
				}
				if (dx < 0 && num == 0)
				{
					rect.left = j * 16 + 16;
				}
			}

			if (TileMap[i][j] == 'c')
			{
				TileMap[i][j] = ' ';
				(*points)++;
			}

			if (TileMap[i][j] == 'a')
			{
				life = false;
			}
			if (TileMap[i][j] == 'x')
			{
				exit = true;
			}

			if (exit &&  TileMap[i][j] == 'Y')
			{
				std::cout << "debug" << std::endl;
				TileMap[i][j] = ' ';
				finish = true;
				break;
			}
		}
}
