#include "Adapter.h"



Adapter::Adapter(Texture &image)
{
	player.life = true;
	player.sprite.setTexture(image);
	player.rect = FloatRect(100, 180, 16, 16);
	player.dx = player.dy = 0.1;
	player.currentFrame = 0;
}


Adapter::~Adapter()
{
}

void Adapter::UpdatePlayer(float time, String *TileMap, float *offsetX, float *offsetY, unsigned int *pointsGame)
{
	player.Update(time, TileMap, offsetX, offsetY, pointsGame);
}
void  Adapter::CollisionPlayer(int num, String *TileMap, unsigned int *pointsGame)
{
	player.Collision(num, TileMap, pointsGame);
}