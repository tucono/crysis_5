#include <SFML/Graphics.hpp>
#include "Bullet.h"

Bullet::Bullet(float xpos, float ypos, float scale, sf::Texture &nTexture)
{
	Sprite.setTexture(nTexture);
}