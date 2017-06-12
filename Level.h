#ifndef LEVEL_H
#define LEVEL_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "TextureManager.h"
#include "Enemy.h"
#include "Player.h"
#include "Background.h"
#include "Bullet.h"
#include "Config.h"

class Level {
private:
	Config cfg;
	TextureManager *textMan;
	sf::RenderWindow *window;
	Background *background;
	Player *player;
	std::vector<Enemy*> enVector;
	sf::Texture plTexture;
	sf::Texture bgTexture;
	sf::Texture enTexture; 
	sf::Texture bulTexture;
	int maxPoints;
public:
	Level(sf::RenderWindow *nWindow, int enNum, int res[2], int nMaxPoints, TextureManager *nTextMan, std::string textures[4]);
	~Level();
	bool main();
};
#endif
