#ifndef ENEMY_h
#define ENEMY_h

#include<SFML/Graphics.hpp>
#include "Character.h"
#include "Gun.h"
class Enemy : public Character{
private:
	//Gun gun;
public:
	Enemy(int xBound, int yBound, float scale, float nFireTime, sf::Texture &nTexture, sf::Texture &bTexture);
	Enemy(float nxpos, float nypos);
	Enemy(const Enemy&) = default;
	//Enemy& operator=(const Enemy& other);
	//Gun &getGun();
	void fireCheck();
	void randPos();
	void randSpeed();
	//void setGunPulse(int nPulse);
	void main();
};

#endif