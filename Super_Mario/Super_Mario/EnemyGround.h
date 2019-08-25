#pragma once
#include "Enemy.h"
class EnemyGround : public Enemy
{
public:
	bool life;
	EnemyGround();
	~EnemyGround();
	
	void Set(Texture &image, int x, int y);
	void Update(float time, bool pLife, String *TileMap, float *offsetX, float *offsetY);
	void Collision(String *TileMap);
	
};


