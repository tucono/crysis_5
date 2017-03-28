#include <SFML/Graphics.hpp>
#include "Bullet.h"

Bullet::Bullet(float xpos, float ypos, float scale, sf::Texture &nTexture)
{
	Sprite.setTexture(nTexture);
	Sprite.setPosition(sf::Vector2f(xpos, ypos));
	Sprite.setScale(sf::Vector2f(scale, scale));
	size[0] = Sprite.getGlobalBounds().width;
	size[1] = Sprite.getGlobalBounds().height;
	boundBox = Sprite.getGlobalBounds();
}

void Bullet::main()
{
	boundBox = Sprite.getGlobalBounds();
	Sprite.move(speed);
}