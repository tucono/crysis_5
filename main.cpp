#include <SFML/Graphics.hpp>
#include <iostream> //for debugging
#include "Enemy.h"
#include "Player.h"
#include "Background.h"
#include "Config.h"
#include "Bullet.h"
#include <vector>

int main(){
	std::string fileLoc = "C:/Users/Philip Thomas/Documents/Visual Studio 2015/Projects/Crysis_5/Crysis_5/Assets/Textures/";//Texture File Location
	Config cfg("C:\\Users\\Philip Thomas\\Documents\\Visual Studio 2015\\Projects\\Crysis_5\\Crysis_5\\Assets\\Config.txt");
	int res[2] = { cfg.getConfig("xres",1000), cfg.getConfig("yres",800)}; // set resolution
	srand(time(0)); //seed rand()
	sf::RenderWindow window(sf::VideoMode(res[0], res[1]), "SFML works!");//create game window
	sf::Texture bgText;
	if (!bgText.loadFromFile(cfg.getConfig("bgTextureLoc", fileLoc + "Space.png"))){
		std::cout << "ERROR IN SPACE TEXTURE LOADING\n";
	}
	Background background(bgText, 0.1, 0, 0, res[1]);
	sf::Texture enTexture; //85 x 107
	if (!enTexture.loadFromFile(cfg.getConfig("enTextureLoc",fileLoc + "koreaEnemy.png"))) {
		std::cout << "ERROR IN ENEMY TEXTURE LOADING\n";
	}
	sf::Texture plTexture; //78 x 108
	if (!plTexture.loadFromFile(cfg.getConfig("plTextureLoc",fileLoc + "playerChar.png"))) {
		std::cout << "ERROR IN PLAYER TEXTURE LOADING\n";
	}
	sf::Texture bulTexture;
	if (!bulTexture.loadFromFile(cfg.getConfig("bulTextureLoc", fileLoc + "laser.png"))) {
		std::cout << "ERROR IN BULLET TEXTURE LOADING\n";
	}
	std::vector<Enemy> enVector;
	for (int i = 0; i < 3; i++){ //generate enemies with multiple positions + speed
		Enemy enemy(res[0] ,res[1], cfg.getConfig("enScale",0.5f) , enTexture); //create new enemy
		enVector.push_back(enemy); //plug it into vector
		enVector[i].setPos(i * 100, 0);
	}

	Player player(200, 200, cfg.getConfig("plSpeed",0.2f), res[0], res[1], cfg.getConfig("plScale",0.5f), plTexture, bulTexture); //xpos, ypos, speed, xbound, ybound, scale, texture
	//player.setPos(200, 200);

	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		//draw all elements here
		background.main();
		window.draw(background.getSprite(0));
		window.draw(background.getSprite(1));

		player.main();
		window.draw(player.getSprite()); //draw Player	 
		std::vector<Bullet>pBulletVect = player.getGun().getBulVect();
		for (std::vector<Bullet>::iterator iter = pBulletVect.begin(); iter != pBulletVect.end(); ++iter) { //draw player bullets
			window.draw(iter->getSprite());
		}
		for (std::vector<Enemy>::iterator i = enVector.begin(); i != enVector.end(); ++i) {
			i->main();
			if (i->getBoundBox().intersects(player.getBoundBox())) {
				i->randPos();
			}
			int index = 0;
			for (std::vector<Bullet>::iterator k = pBulletVect.begin(); k != pBulletVect.end(); ++k) {
				if (i->getBoundBox().intersects(k->getBoundBox())) { //enemy intersects player bullet.
					i->randPos();
					//k->setSpeed(0, 0);
					//k->setPos(player.getPos().x, player.getPos().y); //set bullet to graveyard when hits player.
					player.getGun().getBulVect()[index].setSpeed(0, 0);
					player.getGun().getBulVect()[index].setPos(res[0],res[1]);
				}
				++index;
			}
			window.draw(i->getSprite());//draw Enemies
		}
		window.display();
	}
	return 0;
}