#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
//#include "constants.h"

using namespace sf;

class Player
{
public:
	bool onGround; //На земле ли мы
	float currentFrame; //Текущий кадр для анимации
	float dx, dy; //Скорость
	FloatRect rect; //Вместо ширины\высоты
	Sprite sprite; //Картинка
	bool life;
	bool exit;
	bool finish;
	Player();
	~Player();

	void Update(float time, String *TileMap, float *offsetX, float *offsetY, unsigned int *points);
	void Collision(int num, String *TileMap, unsigned int *points);
};

