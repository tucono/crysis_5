#include <SFML/Graphics.hpp>
#include <iostream> //for debugging
#include "Enemy.h"
#include "Player.h"
#include "Background.h"
#include "Config.h"
#include "Bullet.h"
#include "Level.h"
#include "TextureManager.h"
#include <vector>

int lose(sf::Window *window);

int main(){
	std::string textFileLoc = "C:/Users/Philip Thomas/Documents/Visual Studio 2015/Projects/Crysis_5/Crysis_5/Assets/Textures/";//Texture File Location
	std::string cfgFileLoc = "C:/Users/Philip Thomas/Documents/Visual Studio 2015/Projects/Crysis_5/Crysis_5/Assets/Config.txt";//Config file location
	//Create config file
	Config cfg(cfgFileLoc);
	//create texture manager
	TextureManager textMan(&cfg, textFileLoc);
	// set resolution
	int res[2] = { cfg.getConfig("xres",1000), cfg.getConfig("yres",800)};
	//seed rand()
	srand( int(time(0)));
	//create game window
	sf::RenderWindow window(sf::VideoMode(res[0], res[1]), "SFML works!");
	//Initialize player
	sf::Texture plText = textMan.getTexture("player_01");
	sf::Texture plBulText = textMan.getTexture("bul_01");
	Player player(res[0] / 2, res[1] - 200, cfg.getConfig("plSpeed", 0.2f), cfg.getConfig("plRotSpeed", 0.2f), cfg.getConfig("plSpdMod", 0.00001f), res[0], res[1], cfg.getConfig("plScale", 0.5f),
		cfg.getConfig("plFireTime_inMS", 500.0f), plText, plBulText);
	//Initialize levels
	std::string l1Textures[3] = { "bg_01", "enemy_01", "bul_01" };
	std::vector<Level*> levels;
	levels.push_back(new Level(&window, 3, res, 20, 0, 0, &player, &textMan, l1Textures));//get 20 points to advance
	levels.push_back(new Level(&window, 4, res, 30, 0, 1, &player, &textMan, l1Textures));//survive 30 seconds to advance
	levels.push_back(new Level(&window, 4, res, 60, 0, 2, &player, &textMan, l1Textures));//survive 60 seconds to advance
	/*Level level_0(&window, 3, res, 20, 0, &player, &textMan, l1Textures);//get 20 points to advance
	Level level_1(&window, 4, res, 0, 30, &player, &textMan, l1Textures);//survive 30 seconds to advance
	Level level_2(&window, 4, res, 0, 60, &player, &textMan, l1Textures);//survive 60 seconds to advance*/
	for (std::vector<Level*>::size_type i = 0; i < levels.size(); ++i) {
		if (!levels[i]->main()) {
			return lose(&window);
		}
	}
	std::cout << "Congrats, you beat the game!" << std::endl;
	//Cleanup levels
	for (std::vector<Level*>::size_type i = 0; i < levels.size(); ++i) {
		delete levels[i];
	}
	window.close();
	//TEMPORARY: keeps command window from closing after game window closes for bugfixing
	std::string x;
	std::cin >> x;
	return 0;
}

int lose(sf::Window *window) {
	std::cout << "YOU LOSE!\n";
	window->close();
	std::string x;
	std::cin >> x;
	return 0;
}
