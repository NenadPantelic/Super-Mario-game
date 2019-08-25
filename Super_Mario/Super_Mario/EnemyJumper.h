#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
using namespace sf;
class EnemyJumper : public Enemy
{

public:
	EnemyJumper();
	~EnemyJumper();
	FloatRect rectJ;
	bool active;
	bool intersect;
	void Set(Texture &image, int x, int y);
	void Update(float time, bool pLife, String *TileMap, float *offsetX, float *offsetY);
	void Collision(String *TileMap);
};

