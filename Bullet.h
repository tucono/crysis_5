#ifndef BULLET_h
#define BULLET_h
#include <SFML/Graphics.hpp>
#include "Character.h"

class Bullet: public Character
{
private:

public:
	Bullet(float xpos, float ypos, float scale, sf::Texture &nTexture);
};


#endif
