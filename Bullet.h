#ifndef BULLET_h
#define BULLET_h
#include <SFML/Graphics.hpp>
#include "Character.h"

class Bullet: public Character{
private:

public:
	Bullet(sf::Vector2f nPos, float scale, sf::Texture &nTexture);
	Bullet(sf::Vector2f nPos, float scale); //no texture
	void main();
};

#endif
