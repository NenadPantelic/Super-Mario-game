#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class AdapterPlayer
{
public:
	virtual void UpdatePlayer(float time, String *TileMap) = 0;
	virtual void CollisionPlayer(int num, String *TileMap) = 0;

	virtual bool getOnGround() = 0;
	virtual void setOnGround(bool OnGround) = 0;

	virtual bool getFinish() = 0;

	virtual bool getLife() = 0;
	virtual void setLife(bool Life) = 0;

	virtual bool getExit() = 0;
	virtual void setExit(bool Exit) = 0;

	virtual Sprite getSprite() = 0;
	virtual	void setSprite(Color color) = 0;

	virtual FloatRect getRect() = 0;

	virtual float getDx() = 0;
	virtual void setDx(float Dx) = 0;

	virtual float getDy() = 0;
	virtual void setDy(float Dy) = 0;
};



