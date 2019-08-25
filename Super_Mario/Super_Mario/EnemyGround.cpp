#include "EnemyGround.h"

EnemyGround::EnemyGround()
{
}


EnemyGround::~EnemyGround()
{
}

void EnemyGround::Set(Texture &image, int x, int y)
{
	sprite.setTexture(image);
	rect = FloatRect(x, y, 16, 16);

	dx = 0.05;
	currentFrame = 0;
	life = true;
}

void EnemyGround::Update(float time, bool pLife, String *TileMap, float *offsetX, float *offsetY)
{
	if (pLife) rect.left += dx * time;

	Collision(TileMap);

	//Движение по горизонтали влево\вправо
	currentFrame += time * 0.005;
	if (currentFrame > 2) currentFrame -= 2;

	sprite.setTextureRect(IntRect(18 * int(currentFrame) + 12, 10, 16, 16));

	if (!life) {
		sprite.setTextureRect(IntRect(70, 10, 16, 16));
	}
	sprite.setPosition(rect.left - *offsetX, rect.top - *offsetY);
}

void EnemyGround::Collision(String *TileMap)
{
	for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
		for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
			if ((TileMap[i][j] == 'P') || (TileMap[i][j] == 'b') || (TileMap[i][j] == 'k') || (TileMap[i][j] == '0') || (TileMap[i][j] == 'r') || (TileMap[i][j] == 't'))
			{
				if (dx > 0)
				{
					rect.left = j * 16 - rect.width; dx *= -1;
				}
				else if (dx < 0)
				{
					rect.left = j * 16 + 16;  dx *= -1;
				}
			}

}