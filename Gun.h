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
public:
	Gun();
	std::vector<Bullet> &getBulVect();
	void setTexture(sf::Texture& nText);
	void fire(sf::Vector2f nPos, float speed);
	void main();
};
#endif