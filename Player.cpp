#include <cmath>
#include <iostream>
#include "Player.h"

Player::Player(float nxpos, float nypos, float nSpeed, int xBound, int yBound, float scale, sf::Texture &nTexture)
{
	pos = sf::Vector2f(nxpos, nypos);
	bound[0] = xBound;
	bound[1] = yBound;
	Sprite.setTexture(nTexture);
	setScale(scale, scale);
	boundBox = Sprite.getGlobalBounds();//set bounding box
	setSpeed(nSpeed, nSpeed);
	setSize();
}
Player::Player(float nxpos, float nypos) //simplistic overload
{
	pos = sf::Vector2f(nxpos, nypos);
	Sprite.setColor(sf::Color::Red);
	Sprite.setPosition(pos);
}
void Player::moveCheck()//Movement Grid => right = +, down = +
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && Sprite.getPosition().x + size[0]< bound[0]) //check right
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && Sprite.getPosition().y  > 0)//right+up
			Sprite.move(speed.x * 1 / sqrt(2), -speed.y * 1 / sqrt(2));
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && Sprite.getPosition().y + size[1]< bound[1])//right+down
			Sprite.move(speed.x * 1 / sqrt(2), speed.y * 1 / sqrt(2));
		else //only right
			Sprite.move(speed.x, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && Sprite.getPosition().x  > 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && Sprite.getPosition().y  > 0)//left+up
			Sprite.move(-speed.x * 1 / sqrt(2), -speed.y * 1 / sqrt(2));
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && Sprite.getPosition().y + size[1] < bound[1])//left+down
			Sprite.move(-speed.x * 1 / sqrt(2), speed.y * 1 / sqrt(2));
		else //only left
			Sprite.move(-speed.x, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && Sprite.getPosition().y + size[1] < bound[1])
	{
		Sprite.move(0, speed.y);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && Sprite.getPosition().y  > 0)
	{
		Sprite.move(0, -speed.y);
	}
}
void Player::main()
{
	moveCheck();
}