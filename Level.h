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
	Config *cfg;
	TextureManager *textMan;
	sf::RenderWindow *window;
	Background *background;
	Player *player;
	std::vector<Enemy*> enVector;
	sf::Texture plTexture;
	sf::Texture bgTexture;
	sf::Texture enTexture; 
	sf::Texture bulTexture;
	sf::Clock levelClock;
	sf::Clock enIncClock;
	int res[2];
	int maxPoints;
	float maxTime;
	int levType;
public:
	Level(sf::RenderWindow *nWindow, int enNum, int nRes[2], int nMaxPoints, float nMaxTime, int levType, Player *nPlayer, TextureManager *nTextMan, std::string textures[3], Config *nCfg);
	~Level();
	bool main();
};
#endif
