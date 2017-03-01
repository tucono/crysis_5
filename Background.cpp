#include "Background.h"
#include <vector>

Background::Background(sf::Texture &backTexture, float nSpeed, float nPos[2], float scale)
{
	sf::Sprite sprite1; sf::Sprite sprite2;
	backVec.push_back(sprite1);
	backVec.push_back(sprite2);
	for (std::vector<sf::Sprite>::iterator i = backVec.begin(); i != backVec.end(); ++i) //Iterating through vectors
	{
		i->setTexture(backTexture);
		i->setPosition(sf::Vector2f(nPos[1], nPos[2]));
		i->setScale(scale, scale);
	}
	speed = sf::Vector2f(0, nSpeed);
}

void Background::setPos(float nPos[2])
{
	pos = sf::Vector2f(nPos[1], nPos[2]);
}