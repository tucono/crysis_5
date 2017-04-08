#ifndef ENEMY_h
#define ENEMY_h

#include<SFML/Graphics.hpp>
#include "Character.h"
//class Enemy:Character
class Enemy : public Character{
private:
public:
	Enemy(int xBound, int yBound, float scale, sf::Texture &nTexture);
	Enemy(float nxpos, float nypos);
	void main();
	void randPos();
	void randSpeed();
};

#endif