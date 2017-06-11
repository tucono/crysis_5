#ifndef LEVEL_H
#define LEVEL_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemy.h"
#include "Player.h"
#include "Background.h"
#include "Bullet.h"
#include "Config.h"

class Level {
private:
	Config cfg;
	sf::RenderWindow *window;
	Background *background;
	Player *player;
	std::vector<Enemy*> enVector;
	sf::Texture plTexture;
	sf::Texture bgText;
	sf::Texture enTexture; 
	sf::Texture bulTexture;
	int maxPoints;
public:
	Level(sf::RenderWindow *nWindow, int enNum, int res[2], std::string fileLoc, int nMaxPoints);
	~Level();
	bool main();
};
#endif
