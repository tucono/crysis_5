#ifndef PLAYER_h
#define PLAYER_h

#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Gun.h"
class Player : public Character{
private:
	//Gun gun;
	int score;
public:
	Player(float nxpos, float nypos, float nSpeed, float rSpeed, float nSpeedMod, int xbound, int ybound, float scale, float nFireTime, sf::Texture &pTexture, sf::Texture &bTexture);
	Player(float nxpos, float nypos);
	int getScore();
	//Gun &getGun();
	void moveCheck();
	void fireCheck(); 
	void addScore(int addScore);
	//void setGunPulse(int nGunPulse);
	//void setGunFireAngle(float nAngle);
	void main();
};

#endif