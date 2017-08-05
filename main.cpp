#include <SFML/Graphics.hpp>
#include <iostream> //for debugging
#include "Enemy.h"
#include "Player.h"
#include "Background.h"
#include "Config.h"
#include "Bullet.h"
#include "Level.h"
#include "MainMenu.h"
#include "TextureManager.h"
#include <vector>

int lose(sf::Window *window);

int main() {
	std::string textFileLoc = "Assets/Textures/";//Texture File Location
	std::string cfgFileLoc = "Assets/Config.txt";//Config file location
	//Create config file
	Config cfg(cfgFileLoc);
	//create texture manager
	TextureManager textMan(&cfg, textFileLoc);
	// set resolution
	int res[2] = { cfg.getConfig("xres",1000), cfg.getConfig("yres",800) };
	//seed rand()
	srand(unsigned int(time(0)));
	//create game window
	sf::RenderWindow window(sf::VideoMode(res[0], res[1]), "SFML works!");
	//Initialize player
	sf::Texture plText = textMan.getTexture("player_01");
	sf::Texture plBulText = textMan.getTexture("bul_01");
	Player player(res[0] / 2, res[1] - 200, cfg.getConfig("plSpeed", 0.2f), cfg.getConfig("plRotSpeed", 0.2f), cfg.getConfig("plSpdMod", 0.00001f), res[0], res[1], cfg.getConfig("plScale", 0.5f),
		cfg.getConfig("plFireTime_inMS", 500.0f), 0, plText, plBulText, &cfg);
	
	bool playGame = true;
	MainMenu mainMenu(&window, &textMan, res);
	//Initialize levels
	std::string l1Textures[3] = { "bg_01", "enemy_01", "bul_01" };
	std::vector<Level*> levels;
	levels.push_back(new Level(&window, 3, res, 20, 0, 0, &player, &textMan, l1Textures, &cfg));//get 20 points to advance
	levels.push_back(new Level(&window, 4, res, 30, 0, 1, &player, &textMan, l1Textures, &cfg));//survive 30 seconds to advance
	levels.push_back(new Level(&window, 4, res, 60, 0, 2, &player, &textMan, l1Textures, &cfg));//survive 60 seconds to advance
	
	/*while (playGame) {
		mainMenu.main();
		switch (mainMenu.getOption()) {
		case 3:
			playGame = false;
			break;
		default:
			break;
		}
	}*/
	sf::Event event;
	while (window.isOpen() && playGame) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		mainMenu.main();
		switch(mainMenu.getOption()) {//play game
		case 1:
			for (std::vector<Level*>::size_type i = 0; i < levels.size(); ++i) {
				if (!levels[i]->main()) {
					return lose(&window);
				}
			}
			break;
		case 2:
			std::cout << "This will open to the options menu eventually\n";
			break;
		case 3://quit
			playGame = false;
			break;
		default:
			break;
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