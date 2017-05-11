#ifndef PLAYER_h
#define PLAYER_h
#include <SFML/Graphics.hpp>
#include <thread>
#include <vector>
#include "Character.h"
#include "Gun.h"
class Player : public Character{
private:
	Gun gun;
	sf::Clock fireClock;
	sf::Time dT;
	int sCase;
	//std::vector<Bullet> pBullets;
	//sf::Texture bulText;
public:
	Player(float nxpos, float nypos, double nSpeed, int xbound, int ybound, float scale, sf::Texture &pTexture, sf::Texture &bTexture);
	Player(float nxpos, float nypos);
	Gun &getGun();
	//std::vector<Bullet> getBulVect();
	void moveCheck();
	void fireCheck(); 
	//void fire();
	void main();
};

#endif