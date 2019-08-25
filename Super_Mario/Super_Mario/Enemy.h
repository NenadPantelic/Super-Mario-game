#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
class Enemy
{
public:
	float dx, dy; 
	FloatRect rect;
	bool onGround;
	Sprite sprite;
	float currentFrame; 

	virtual	void Set(Texture &image, int x, int y) = 0;

	virtual void Update(float time, bool pLife, String *TileMap, float *offsetX, float *offsetY) = 0;

	virtual void Collision(String *TileMap) = 0;
};


