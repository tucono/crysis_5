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
	sCase = 0;
}
/*Gun& Gun::operator =(const Gun& other) {
	cfg = other.cfg;
	bulVect = other.bulVect;
	bulText = other.bulText;
	fireClock = other.fireClock;
	dT = other.dT;
	nBulPos = other.nBulPos;
	nBulSpeed = other.nBulSpeed;
	sCase = other.sCase;
}*/
std::vector<Bullet> &Gun::getBulVect(){
	return bulVect;
}
int Gun::getFireCase() {
	return sCase;
}
void Gun::setTexture(sf::Texture& nTexture) {
	bulText = nTexture;
}
void Gun::fire(sf::Vector2f nPos, float speed) {
	for (std::vector<Bullet>::iterator i = bulVect.begin(); i != bulVect.end(); i++) {//Check unused bullets first
		if (!i->getShot()) { //if unused found, use it and don't create a new one.
			i->setPos(nPos);
			i->setSpeed(0, speed);
			i->setShot(true);
			return;
		}
	}
	float scale = 0.1; //will change to give actual scale later
	Bullet bullet(nPos, scale, bulText);
	bullet.setSpeed(0, speed);
	bulVect.push_back(bullet);
}
void Gun::fireCheck() {
	switch (sCase) {
	case 1:
		fireClock.restart();//start timer from 0
		dT = fireClock.getElapsedTime();
		fire(nBulPos, nBulSpeed);
		++sCase;
		break;
	case 2:
		dT = fireClock.getElapsedTime();
		if (dT.asMilliseconds() > 500) { //wait 1/2 second
			sCase = 0; //wait until fireCheck is called again
		}
		break;
	default:
		fireClock.restart();//prevents fireClock from continously building as game progresses
		sCase = 0;//keep sCase 0 unless firing
		break;
	}
}
void Gun::fireCheck(sf::Vector2f nPos, float nSpeed) { //Initialize fireCheck() values
	nBulPos = nPos;
	nBulSpeed = nSpeed;
	sCase = 1;
}
void Gun::main() {
	for (std::vector<Bullet>::iterator i = bulVect.begin(); i != bulVect.end(); i++) {//loop through all bullets
		i->main();
	}
	fireCheck();
}