#ifndef ENEMY_h
#define ENEMY_h

#include<SFML/Graphics.hpp>
#include "Character.h"
#include "Gun.h"
class Enemy : public Character{
private:
	//Gun gun;
public:
	Enemy(int xBound, int yBound, float scale, float nFireTime, int nGunType, sf::Texture &nTexture, sf::Texture &bTexture, Config *nCfg);
	~Enemy();
	//Enemy(const Enemy&) = default;
	void fireCheck();
	void randPos();
	void randSpeed();
	void main();
};

#endif