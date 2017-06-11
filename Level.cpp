#include "Level.h"
#include <iostream>

Level::Level(sf::RenderWindow *nWindow, int enNum, int res[2], std::string fileLoc, int nMaxPoints) {
	// Load textures (WILL BE DONE WITH TEXTURE MANAGER
	if (!plTexture.loadFromFile(cfg.getConfig("plTextureLoc", fileLoc + "playerChar.png"))) {
		std::cout << "ERROR IN PLAYER TEXTURE LOADING\n";
	}
	if (!bgText.loadFromFile(cfg.getConfig("bgTextureLoc", fileLoc + "Space.png"))) {
		std::cout << "ERROR IN SPACE TEXTURE LOADING\n";
	}
	if (!enTexture.loadFromFile(cfg.getConfig("enTextureLoc", fileLoc + "koreaEnemy.png"))) {
		std::cout << "ERROR IN ENEMY TEXTURE LOADING\n";
	}
	if (!bulTexture.loadFromFile(cfg.getConfig("bulTextureLoc", fileLoc + "laser.png"))) {
		std::cout << "ERROR IN BULLET TEXTURE LOADING\n";
	}
	// Initialize player, enemies, and background
	background = new Background(bgText, 0.1, 0, 0, res[1]);
	player = new Player(res[0] / 2, res[1] - 200, cfg.getConfig("plSpeed", 0.2f), cfg.getConfig("plRotSpeed", 0.2f), cfg.getConfig("plSpdMod", 0.00001f), res[0], res[1], cfg.getConfig("plScale", 0.5f), cfg.getConfig("plFireTime_inMS", 500), plTexture, bulTexture);
	for (int i = 0; i < enNum; ++i) {
		enVector.push_back(new Enemy(res[0], res[1], cfg.getConfig("enScale", 0.5f), cfg.getConfig("enFireTime_inMS", 500), enTexture, bulTexture));
	}
	//Setup render window
	window = nWindow;
	maxPoints = nMaxPoints;
}
Level::~Level() {
	//Remove references;
	delete player;
	delete background;
	for (std::vector<Enemy*>::size_type n = 0; n < enVector.size(); ++n) {
		delete enVector[n];
		//enVector.erase[n];
	}
}
bool Level::main() {
	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window->close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {//exit game
			return 0;
			//window->close();
		}
		if (player->getHealth() <= 0) {
			//window->close();
			std::cout << "YOU LOSE\n";
			return 0;
		}
		if (player->getScore() > maxPoints) { //points needed to go to next level
			std::cout << "You Win!\n";
			return 1;
		}

		//Iterate through all element behaviors
		background->main();
		player->main();
		window->clear();

		//draw all elements here
		window->draw(background->getSprite(0));
		window->draw(background->getSprite(1));
		window->draw(player->getSprite()); //draw Player	 
		for (std::vector<Bullet>::size_type i = 0; i < player->getGun().getBulVect().size(); ++i) { //draw player bullets
			window->draw(player->getGun().getBulVect()[i].getSprite());
		}
		for (std::vector<Enemy*>::size_type n = 0; n < enVector.size(); ++n) { //BREAKS DUE TO ERROR ABOVE
			enVector[n]->main();
			if (enVector[n]->getBoundBox().intersects(player->getBoundBox())) {//enemy hits player
				enVector[n]->randPos();
				player->damage(10);
				std::cout << "You're hit! Your health is at: " << player->getHealth() << std::endl;
			}
			int index = 0;
			for (std::vector<Bullet>::size_type k = 0; k < player->getGun().getBulVect().size(); ++k) {
				if (enVector[n]->getBoundBox().intersects(player->getGun().getBulVect()[k].getBoundBox())) { //enemy intersects player bullet.
					enVector[n]->randPos();
					player->getGun().getBulVect()[index].setCurSpeed(0, 0);
					player->getGun().getBulVect()[index].setPos(sf::Vector2f(-100, -100));
					player->getGun().getBulVect()[index].setShot(false);//set shot as unused
					player->addScore(1);
				}
				++index;
			}
			for (std::vector<Bullet>::size_type j = 0; j < enVector[n]->getGun().getBulVect().size(); ++j) {
				if (player->getBoundBox().intersects(enVector[n]->getGun().getBulVect()[j].getBoundBox())) {//player intersects enemy bullet
					enVector[n]->getGun().getBulVect()[j].setCurSpeed(0, 0);
					enVector[n]->getGun().getBulVect()[j].setPos(sf::Vector2f(-100, -100));
					enVector[n]->getGun().getBulVect()[j].setShot(false);
					player->damage(5);
					std::cout << "You're hit! Your health is at: " << player->getHealth() << std::endl;
				}
			}
			index = 0;
			for (std::vector<Bullet>::size_type j = 0; j < enVector[n]->getGun().getBulVect().size(); ++j) { //iterate through enemy bullets
				window->draw(enVector[n]->getGun().getBulVect()[index].getSprite());
				++index;
			}
			window->draw(enVector[n]->getSprite());//draw Enemies
		}
		window->display();
	}
	return 0;
}