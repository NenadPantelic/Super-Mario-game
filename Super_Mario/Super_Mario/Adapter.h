#pragma once
#include "Player.h"

class Adapter
{
private:
	Player player;
public:
	Adapter(Texture &image);
	~Adapter();

	bool getFinish() { return player.finish; }

	bool getExit() { return player.exit; }
	void setExit(bool Exit) { player.exit = Exit; };

	bool getOnGround() { return player.onGround; }
	void setOnGround(bool OnGround) { player.onGround = OnGround; }

	bool getLife() { return player.life; }
	void setLife(bool Life) { player.life = Life; }

	Sprite getSprite() { return player.sprite; }
	void setSprite(Color color) { player.sprite.setColor(color); }

	FloatRect getRect() { return player.rect; }

	float getDx() { return player.dx; }
	void setDx(float Dx) { player.dx = Dx; }

	float getDy() { return player.dy; }
	void setDy(float Dy) { player.dy = Dy; }

	void setPlayer(Player playerInstance) { player = playerInstance; }
	Player getPLayer() { return player; }

	void UpdatePlayer(float time, String *TileMap, float *offsetX, float *offsetY, unsigned int *pointsGame);
	void CollisionPlayer(int num, String *TileMap, unsigned int *pointsGame);


};





