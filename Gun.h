#ifndef GUN_h
#define GUN_h
#include <vector>
#include <SFML/Graphics.hpp>
#include "Config.h"
#include "Bullet.h"

class Gun {
private:
	Config cfg;
	std::vector<Bullet> bulVect;
	sf::Texture bulText;
	sf::Clock fireClock;
	sf::Time dT;
	sf::Vector2f nBulPos;
	float nBulSpeed;
	float nBulRot;
	float minFireTime;
	int sCase;
	int bound[2];
public:
	Gun();
	//Gun(const Gun&) = default;
	//Gun& operator =(const Gun& other);
	std::vector<Bullet> &getBulVect();
	int getFireCase();
	void setTexture(sf::Texture& nText);
	void setBound(int xBound, int yBound);
	void fire(sf::Vector2f nPos, float rot, float speed);
	void fireCheck();
	void fireCheck(sf::Vector2f nPos, float nRot, float nSpeed, float nMinFireTime);
	void main();
};
#endif