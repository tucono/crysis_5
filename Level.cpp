#include "Level.h"
#include <iostream>

Level::Level(sf::RenderWindow *nWindow, int enNum, int nRes[2], int nMaxPoints, float nMaxTime, int levType, Player *nPlayer, TextureManager *nTextMan, std::string textures[3]) {
	//Set boundary through resolution
	res[0] = nRes[0];
	res[1] = nRes[1];
	// Load textures
	textMan = nTextMan;
	bgTexture = textMan->getTexture(textures[0]);
	enTexture = textMan->getTexture(textures[1]);
	bulTexture = textMan->getTexture(textures[2]);
	// Initialize player, enemies, and background
	background = new Background(bgTexture, 0.1f, 0, 0, float(res[1]));
	player = nPlayer;
	for (int i = 0; i < enNum; ++i) {
		enVector.push_back(new Enemy(res[0], res[1], cfg.getConfig("enScale", 0.5f), cfg.getConfig("enFireTime_inMS", 500.0f), enTexture, bulTexture));
	}
	//Setup render window
	window = nWindow;
	//Set level win conditions
	maxPoints = nMaxPoints;
	maxTime = nMaxTime;
}
Level::~Level() {
	//Remove references;
	//delete player;
	delete background;
	for (std::vector<Enemy*>::size_type n = 0; n < enVector.size(); ++n) {
		delete enVector[n];
		//enVector.erase[n];
	}
}
bool Level::main() {
	levelClock.restart();
	float dT;
	int enIncCase = 0;
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
		//Level Types
		switch (levType) {
		case 0: //Advance by points
			if (player->getScore() > maxPoints) { //points needed to go to next level
				std::cout << "You Win!\n";
				return 1;
			}
			break;
		case 1: //Advance by time
			if (levelClock.getElapsedTime().asSeconds() >= maxTime) {
				std::cout << "You Win!\n";
				return 1;
			}
			break;
		case 2: //Advance by time, enemies increase with time
			if (levelClock.getElapsedTime().asSeconds() >= maxTime) {
				std::cout << "You Win!\n";
				return 1;
			}
			switch (enIncCase) {
			case 0:
				enIncClock.restart();
				++enIncCase;
				break;
			case 1:
				dT = enIncClock.getElapsedTime().asSeconds();
				if (dT > 10) {
					enVector.push_back(new Enemy(res[0], res[1], cfg.getConfig("enScale", 0.5f), cfg.getConfig("enFireTime_inMS", 500.0f), enTexture, bulTexture));
					enIncCase = 0;
				}
				break;
			default:
				enIncClock.restart();
				break;
			}
			
			break;
		default: //Advance by points
			if (player->getScore() > maxPoints) { //points needed to go to next level
				std::cout << "You Win!\n";
				return 1;
			}
			break;
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