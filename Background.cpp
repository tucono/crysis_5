#include "Background.h"
#include <vector>

Background::Background(sf::Texture &backTexture, float nSpeed, float xPos, float yPos, float scale)
{
	sf::Sprite sprite1; sf::Sprite sprite2;
	backVec.push_back(sprite1);
	backVec.push_back(sprite2);
	for (std::vector<sf::Sprite>::iterator i = backVec.begin(); i != backVec.end(); ++i) //Iterating through vectors
	{
		i->setTexture(backTexture);
		i->setPosition(sf::Vector2f(xPos, yPos));
		i->setScale(scale, scale);
	}
	speed = sf::Vector2f(0, nSpeed);
}

void Background::setPos(float nPos[2])
{
	pos = sf::Vector2f(nPos[1], nPos[2]);
}
void Background::setSpeed(float nSpeed)
{
	speed.y = nSpeed;
}
void Background::setScale(float nScale)
{
	scale.x = nScale;
	scale.y = nScale;
	for (std::vector<sf::Sprite>::iterator i = backVec.begin(); i != backVec.end(); ++i)
	{
		i->setScale(scale.x, scale.y);
	}
}
void Background::flipOrient()
{
	orient *= -1;
}
std::vector<sf::Sprite> Background::getSpriteVector()//theoretical?
{
	return backVec;
}
sf::Sprite Background::getSprite(std::vector<sf::Sprite>::size_type i)
{
	return backVec[i];
}
sf::Vector2f Background::getSpeed()
{
	return speed;
}

void Background::main()
{
	if (orient && iter == 0)//if orient = 1, back 0 is on top
	{
		backVec[0].setPosition(0, 0);
		backVec[1].setPosition(0, backVec[0].getGlobalBounds().height); //need to check if works
	}
	else if (!orient && iter == 0)//if orient = 0, back 1 is on top		
	{
		backVec[1].setPosition(0, 0);
		backVec[0].setPosition(0, backVec[1].getGlobalBounds().height);
	}
	else
	{
		backVec[0].move(speed);
		backVec[1].move(speed);
	}
}