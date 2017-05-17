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
	Config cfg("C:\\Users\\Philip Thomas\\Documents\\Visual Studio 2015\\Projects\\Crysis_5\\Crysis_5\\Assets\\Config.txt");//Create config file
	int res[2] = { cfg.getConfig("xres",1000), cfg.getConfig("yres",800)}; // set resolution
	srand(time(0)); //seed rand()
	sf::RenderWindow window(sf::VideoMode(res[0], res[1]), "SFML works!");//create game window
	//Load Textures (WILL BE MOVED TO A TEXTURE MANAGER)
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
	//Generate entities
	Enemy enemy(res[0], res[1], cfg.getConfig("enScale", 0.5f), enTexture, bulTexture); //creating enemy [TESTING ONLY, NEEDS TO GO IN VECTOR]
	enemy.setPos(sf::Vector2f(1 * 100, 0));
	std::vector<Enemy*> enVector;
	enVector.push_back(&enemy);//Works, need to find solution where I can create enemies in a for loop
	//BROKEN: ATTEMPTING TO REFERENCE DELETED FUNCTION
	/*for (int i = 0; i < 3; i++){ //generate enemies with multiple positions + speed
		Enemy enemy(res[0] ,res[1], cfg.getConfig("enScale",0.5f) , enTexture, bulTexture); //create new enemy
		enVector.push_back(enemy); //uses definition of vector<Enemy>
		enVector[i].setPos(sf::Vector2f(i * 100, 0));
	}*/
	Player player(res[0]/2, res[1]-200, cfg.getConfig("plSpeed",0.2f), res[0], res[1], cfg.getConfig("plScale",0.5f), plTexture, bulTexture); //xpos, ypos, speed, xbound, ybound, scale, texture
	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))//exit game
			window.close();

		//Iterate through all element behaviors
		background.main();
		enemy.main();
		player.main();
		window.clear();

		//draw all elements here
		window.draw(background.getSprite(0));
		window.draw(background.getSprite(1));
		window.draw(player.getSprite()); //draw Player	 
		for (std::vector<Bullet>::size_type i = 0; i < player.getGun().getBulVect().size(); ++i) { //draw player bullets
			window.draw(player.getGun().getBulVect()[i].getSprite());
		}
		window.draw(enemy.getSprite()); //draw enemy
		for (std::vector<Bullet>::size_type n = 0; n < enemy.getGun().getBulVect().size(); ++n) { //draw enemy bullets
			window.draw(enemy.getGun().getBulVect()[n].getSprite());
		}
		/*for (std::vector<Enemy*>::size_type n = 0; n < enVector.size(); ++n) { //BREAKS DUE TO ERROR ABOVE
			enVector[n]->main();
			if (enVector[n]->getBoundBox().intersects(player.getBoundBox())) {
				enVector[n]->randPos();
			}
			int index = 0;
			for (std::vector<Bullet>::iterator k = pBulletVect.begin(); k != pBulletVect.end(); ++k) {
				if (enVector[n]->getBoundBox().intersects(k->getBoundBox())) { //enemy intersects player bullet.
					enVector[n]->randPos();
					player.getGun().getBulVect()[index].setSpeed(0, 0);
					player.getGun().getBulVect()[index].setPos(sf::Vector2f(-100,-100));
					player.getGun().getBulVect()[index].setShot(false);//set shot as unused
				}
				++index;
			}
			window.draw(enVector[n]->getSprite());//draw Enemies
		}*/
		window.display();
	}
	return 0;
}