#ifndef BULLET_h
#define BULLET_h
#include <SFML/Graphics.hpp>
#include "Character.h"

class Bullet: public Character{
private:
	bool shot;
public:
	Bullet(sf::Vector2f nPos, float scale, sf::Texture &nTexture);
	Bullet(sf::Vector2f nPos, float scale); //no texture
	bool getShot(); //return if it is shot or not
	void setShot(bool status);
	void main();
};

#endif
