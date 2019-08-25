#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>


#include "constants.h"
#include "Player.h"
#include "EnemyGround.h"
#include "EnemyJumper.h"
#include "Adapter.h"

using namespace std;
using namespace sf;


std::ostringstream playerScore, playerTime;
void startGame(String *TileMap);
RenderWindow win(VideoMode(600, 270), "Super Mario");


void setEnemyPosition(Enemy *enemy, Texture &image, int x, int y)
{
	(*enemy).Set(image, x, y);
}

void startGame(String *TileMap)
{

	Font font;
	font.loadFromFile("arial.ttf");
	Text text("", font, 20);
	text.setFillColor(Color::Red);
	text.setStyle(sf::Text::Bold);


	Texture coin;
	coin.loadFromFile("images/CoinForWater.gif");

	Texture enemyTexture;
	enemyTexture.loadFromFile("images/goomba.png");

	Texture enemyJumperTexture;
	enemyJumperTexture.loadFromFile("images/jumper_trans_sprite.gif");

	Texture princess;
	princess.loadFromFile("images/Princess.png");


	Texture blocks;
	blocks.loadFromFile("images/blocks.png");


	Texture castle;
	castle.loadFromFile("images/castle_trans.png");

	Texture lava;
	lava.loadFromFile("images/lava_trans.png");

	Texture pipe;
	pipe.loadFromFile("images/pipe_trans.png");

	Texture mario;
	mario.loadFromFile("images/mario_trans.png");

	Adapter Mario(mario);
	EnemyGround enemy[10];
	EnemyJumper enemyJump[10];
	pointsGame = 0;
	int timeG1 = 0, timeG2 = 0, timeG3 = 0;
	offsetX = 0, offsetY = 0;
	Mario.setExit(false);


	Sprite coinSprite(coin);
	Sprite redBlock(blocks);
	Sprite solidRedBlock(blocks);
	Sprite solidBlueRock(blocks);
	Sprite pipeSprite(pipe);
	Sprite princessSprite(princess);
	Sprite castleSprite(castle);
	Sprite lavaSprite(lava);
	Sprite tunelSprite(castle);

	coinSprite.setTextureRect(IntRect(0, 0, 10, 14));
	redBlock.setTextureRect(IntRect(2, 3, 16, 16));
	solidRedBlock.setTextureRect(IntRect(15, 2, 16, 16));
	solidBlueRock.setTextureRect(IntRect(15, 18, 16, 16));
	pipeSprite.setTextureRect(IntRect(24, 8, 48, 60));
	princessSprite.setTextureRect(IntRect(0, 2, 16, 16));
	castleSprite.setTextureRect(IntRect(0, 0, 123, 98));
	lavaSprite.setTextureRect(IntRect(1, 1, 17, 17));
	tunelSprite.setTextureRect(IntRect(55, 82, 16, 16));
	Sprite spriteArr[] = { coinSprite, redBlock, solidRedBlock, solidBlueRock, pipeSprite, princessSprite, castleSprite, lavaSprite, tunelSprite };
	int spriteIndex = 0;
	map<char, int> textureIndexMap = {

			{'Y', 5},
			{'P', 1},
			{'c', 0},
			{'t', 4},
			{ 'r', 2},
			{'b', 3},
			{'Z', 6},
			{'a', 7},
			{'h', 8}

	};

	/*these arrays determine positions of enemies*/
	int enemyXPos[numOfGroundEnemies - 2] = { 21,  56, 21, 28, 60, 64, 110, 120 };
	int enemyYPos[numOfGroundEnemies - 2] = { 13,  13, 6, 6, 6, 6, 6, 6 };

	int flyingEnemyXPos[numOfGroundEnemies-1] = { 18, 25,  50, 59, 66, 88, 95, 108, 122 };
	int flyingEnemyYPos[numOfGroundEnemies-1] = { 13, 13, 13, 13, 13, 13, 13, 13, 13 };


	Clock clock;
	Sprite exitS;
	FloatRect exitFR;
	bool mT = true;
	for (int i = 0; i < numOfGroundEnemies; i++) {
		setEnemyPosition(enemy + i, enemyTexture, enemyXPos[i] * 16, enemyYPos[i] * 16);
		setEnemyPosition(enemyJump + i, enemyJumperTexture, flyingEnemyXPos[i] * 16, flyingEnemyYPos[i] * 16);
	}


	while (win.isOpen())
	{
		if (menuT) timeG3 += timeG2;
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		if (Mario.getLife())
		{
			timeGame = timeG1 - timeG3;
			menuT = false;
		}

		time = time / 1000;

		if (time > 20) time = 20;

		Event event;
		while (win.pollEvent(event))
		{
			if (event.type == Event::Closed)
				win.close();
		}
		if (Mario.getLife())
		{
			if (Keyboard::isKeyPressed(Keyboard::Left))
				Mario.setDx(-0.1);

			if (Keyboard::isKeyPressed(Keyboard::Right))
				Mario.setDx(0.1);

			if (Keyboard::isKeyPressed(Keyboard::Up))

				if (Mario.getOnGround())
				{
					Mario.setDy(-0.27); Mario.setOnGround(false);
				}
		}

		Mario.UpdatePlayer(time, TileMap, &offsetX, &offsetY, &pointsGame);

		for (int i = 0; i < 10; i++)
			enemy[i].Update(time, Mario.getLife(), TileMap, &offsetX, &offsetY);
		for (int i = 0; i < 10; i++)
			enemyJump[i].Update(time, Mario.getLife(), TileMap, &offsetX, &offsetY);

		for (int i = 0; i < 10; i++)
		{
			if (Mario.getRect().intersects(enemy[i].rect))
			{
				if (enemy[i].life)
				{
					if (Mario.getDy() > 0) { enemy[i].dx = 0; Mario.setDy(-0.2); enemy[i].life = false; }
					else
					{
						Mario.setLife(false);
					}
				}
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if (Mario.getRect().intersects(enemyJump[i].rectJ))
			{
				if (Mario.getRect().intersects(enemyJump[i].rect))
				{
					if (enemyJump[i].active)
					{
						Mario.setLife(false);
					}
				}
				enemyJump[i].intersect = true; 	enemyJump[i].active = true;
			}
			else { enemyJump[i].intersect = false; enemyJump[i].active = false; }
		}

		if (Mario.getRect().left > 200) offsetX = Mario.getRect().left - 200;

		if (!level) win.clear(Color(60, 80, 255));
		if (level) win.clear(Color(20, 0, 50));

		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++)
			{
				if ((TileMap[i][j] == ' ') || (TileMap[i][j] == '0') || (TileMap[i][j] == 'x')) continue;
				spriteIndex = textureIndexMap[TileMap[i][j]];
				spriteArr[spriteIndex].setPosition(j * 16 - offsetX, i * 16 - offsetY);
				win.draw(spriteArr[spriteIndex]);

			}

		}

		std::ostringstream playerScore, playerTime;
		playerScore << pointsGame;
		text.setString(L"Points: " + playerScore.str());
		text.setPosition(16, 0);

		for (int i = 0; i < 10; i++)
			win.draw(enemy[i].sprite);
		for (int i = 0; i < 10; i++)
			win.draw(enemyJump[i].sprite);

		win.draw(text);
		win.draw(Mario.getSprite());

		win.display();
		if (!Mario.getLife())
		{
			startGame(TileMap);
		}
		if (Mario.getFinish())
		{
			startGame(TileMap);
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			menuT = true;

		}
	}
}

void runGame()
{

	String 	TileMap[H] = {
"b000000000000000000000000b000000000000000000000000000000000000000000000000000000000000000000000000000000b000000000000000bbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
"b                        b                                                                              b               bbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
"b                      bbbbb                                                                            b          c   bbbbbbbbrrrrrbrrrrrbbrrrrrbbrrb",
"b                        b                                                                              b        bbbbbbbbbbbbbbrbbbrbbbrbbbbrbbbbbbrrb",
"b                        b                                                                                              bbbbbbbrrrrrbbbrbbbbrrrrrbbrrb",
"b                        b                                                               bbbbbb                         bbbbbbbrbbrbbbbrbbbbbbbbrbbrrb",
"b               r       c c     r                         bc        cb                                      b  c        cbbbbbbrbbbrbbbrbbbbrrrrrbbrrb",
"b              bbbbbbbbbbbbbbbbbbb                        bbbbbbbbbbbb            b  b            bbbbbbbb  bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
"b                                    b              r                       r                                     Z            bbbbbbbbbbbbbbbbbbbbbbb",
"b                    c      c       b b     c     c              c          r                              c                    bbbbbbbbbbbbbbbbbbbbbb",
"b                                  b   b        bb        r                rr                                                   bbbbbbbbbbbbbbbbbbbbbb",
"b           t0                    b     t0      b        rr               rrr       t0                                         bbbbbbbbbbbbbbbbbbbbbbb",
"b           00                   b      00  r   b       rrr              rrrr       00              r                          bbbbbbbbbbbbbbbbbbbbbbb",
"b           00                  b       00      b   c   rrr              rrrr       00       c     rr           x             cbbbbbbbbbbbbbbbbbbbbbbb",
"PPPPPPP    PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP     PPPPPPPPPPPPPPPPPPPPPPPPPPPPP      PPPPPPPPPPPPPPPPPP     PPPPPPPPPPPhhPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPaaaaaPPPPPPPPPPPPPPPPPPPPPPPPPPPPPaaaaaaPPPPPPPPPPPPPPPPPPaaaaaPPPPPPPPPPPhhhhhhhhhhhhhhhhhhhhhhhhhhYhhhhhh",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPaaaaaPPPPPPPPPPPPPPPPPPPPPPPPPPPPPaaaaaaPPPPPPPPPPPPPPPPPPaaaaaPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
	};

	startGame(TileMap);

}

int main()
{
	runGame();
	return 0;
}


/*
b - plava ploca
r - crvena ploca
P - podloga
a - lava
t000 - pipe
w - oblak
c - kristal
Y - kljuc
Z - zastava
x - zamak


*/