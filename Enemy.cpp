#include "Enemy.h"
#include "Character.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>

Enemy::Enemy(int xBound, int yBound, float scale, sf::Texture &nTexture)
{
	//pos = sf::Vector2f(nxpos, nypos);
	bound[0] = xBound;
	bound[1] = yBound;
	Sprite.setTexture(nTexture);
	setScale(scale, scale);
	boundBox = Sprite.getGlobalBounds();//set bounding box
	//setPos(pos[0], pos[1]);
	randPos();
	randSpeed();
}
Enemy::Enemy(float nxpos, float nypos) //simplistic overload
{
	pos = sf::Vector2f(nxpos, nypos);
	Sprite.setColor(sf::Color::Red);
	Sprite.setPosition(pos);

}
void Enemy::randSpeed()
{
	speed.x = 0;
	//speed.y = (rand()%10 + 1)*0.01f;
	speed.y = 0.1f;
}
void Enemy::randPos()
{
	Sprite.setPosition(sf::Vector2f(rand() % (bound[0]+getSize()[0]*int(scale.x)*2) - getSize()[0] * int(scale.x) * 2, 0)); // still needs fix to always spawn in render window

}
void Enemy::main()
{
	Sprite.move(speed);
	pos = Sprite.getPosition();
	if (getPos().y + getSize()[1] > bound[1])
	{
		randPos(); //reset it back to top
		randSpeed();
	}
}