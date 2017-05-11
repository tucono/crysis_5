#include "SFML/Graphics.hpp"
#include "Gun.h"
#include "Bullet.h"
#include <string>
#include <iostream>

Gun::Gun() {
	cfg = Config("C:\\Users\\Philip Thomas\\Documents\\Visual Studio 2015\\Projects\\Crysis_5\\Crysis_5\\Assets\\Config.txt");
	sf::Texture nText;
	if (!nText.loadFromFile(cfg.getConfig("bulTextLoc", "C:/Users/Philip Thomas/Documents/Visual Studio 2015/Projects/Crysis_5/Crysis_5/Assets/Textures/laser.png"))) {//need to replace with variable storing default fileloc
		std::cout << "ERROR LOADING BULLET TEXTURE\n";
	}
	bulText = nText;
	Bullet bullet(sf::Vector2f(0,0), 0, bulText);
	bulVect.push_back(bullet);
}
std::vector<Bullet> &Gun::getBulVect(){
	return bulVect;
}
void Gun::setTexture(sf::Texture& nTexture) {
	bulText = nTexture;
}
void Gun::fire(sf::Vector2f nPos, float speed) {
	float scale = 0.1; //will change to give actual scale later
	Bullet bullet(nPos, scale, bulText);
	bullet.setSpeed(0, speed);
	bulVect.push_back(bullet);
	std::cout << "In gun->fire\n";
}
void Gun::main() {
	for (std::vector<Bullet>::iterator i = bulVect.begin(); i != bulVect.end(); i++) {//loop through all bullets
		i->main();
	}
}