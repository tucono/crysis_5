#include <SFML/Graphics.hpp>
#include <iostream> //for debugging
#include "Enemy.h"
#include "Player.h"
#include "Background.h"
#include "Config.h"
#include <vector>

int main(){
	std::string fileLoc = "C:\\Users\\Philip Thomas\\Documents\\Visual Studio 2015\\Projects\\Crysis_5\\Textures\\";//Texture File Location
	int res[2] = { 1000, 800 }; // set resolution
	srand(time(0)); //seed rand()
	Config cfg("C:\\Users\\Philip Thomas\\Documents\\Visual Studio 2015\\Projects\\Crysis_5\\Crysis_5\\Assets\\Config.txt");
	float test = cfg.getConfigFloat("test", 0.0f);//test config
	float N = cfg.getConfigFloat("new", 10.1);
	std::cout << test << " " << N << std::endl;
	sf::RenderWindow window(sf::VideoMode(res[0], res[1]), "SFML works!");//create game window
	sf::Texture bgText;
	if (!bgText.loadFromFile(fileLoc + "Space.png")){
		std::cout << "ERROR IN SPACE TEXTURE LOADING\n";
	}
	Background background(bgText, 0.1, 0, 0, res[1]);
	sf::Texture enTexture; //85 x 107
	if (!enTexture.loadFromFile(fileLoc + "koreaEnemy.png")) {
		std::cout << "ERROR IN ENEMY TEXTURE LOADING\n";
	}
	sf::Texture plTexture; //78 x 108
	if (!plTexture.loadFromFile(fileLoc + "playerChar.png")){
		std::cout << "ERROR IN PLAYER TEXTURE LOADING\n";
	}
	std::vector<Enemy> enVector;
	for (int i = 0; i < 3; i++){ //generate enemies with multiple positions + speed
		Enemy enemy(res[0] ,res[1], 0.5 , enTexture); //create new enemy
		enVector.push_back(enemy); //plug it into vector
		enVector[i].setPos(i * 100, 0);
	}

	Player player(res[0] / 2, 900, 0.2f, res[0], res[1], 0.5, plTexture); //xpos, ypos, speed, xbound, ybound, scale, texture
	player.setPos(200, 200);

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

		for (std::vector<Enemy>::iterator i = enVector.begin(); i != enVector.end(); ++i){
			i->main();
			for (std::vector<Enemy>::iterator k = enVector.begin(); k != enVector.end(); ++k){
				if (k != i){
					if (i->getBoundBox().intersects(k->getBoundBox())){
						i->randPos();
					}
				}
				if (i->getBoundBox().intersects(player.getBoundBox())){
					i->randPos();
				}
			}
			window.draw(i->getSprite());//draw Enemies
		}
		player.main();
		window.draw(player.getSprite()); //draw Player	 
		window.display();
	}
	return 0;
}