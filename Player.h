#ifndef PLAYER_h
#define PLAYER_h

#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Gun.h"
class Player : public Character{
private:
	Gun gun;
public:
	Player(float nxpos, float nypos, float nSpeed, float rSpeed, int xbound, int ybound, float scale, float nFireTime, sf::Texture &pTexture, sf::Texture &bTexture);
	Player(float nxpos, float nypos);
	Gun &getGun();
	void moveCheck();
	void fireCheck(); 
	void main();
};

#endif