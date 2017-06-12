#define _USE_MATH_DEFINES

//#include "SFML/Graphics.hpp"
#include "Gun.h"
#include "Bullet.h"
#include <string>
#include <iostream>
#include <cmath>

Gun::Gun() {
	cfg = Config("C:\\Users\\Philip Thomas\\Documents\\Visual Studio 2015\\Projects\\Crysis_5\\Crysis_5\\Assets\\Config.txt");
	sf::Texture nText;
	if (!nText.loadFromFile(cfg.getConfig("bulTextLoc", "C:/Users/Philip Thomas/Documents/Visual Studio 2015/Projects/Crysis_5/Crysis_5/Assets/Textures/laser.png"))) {//need to replace with variable storing default fileloc
		std::cout << "ERROR LOADING BULLET TEXTURE\n";
	}
	bulText = nText;
	Bullet bullet(sf::Vector2f(0,0), 0, 0, 0, bulText);
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
void Gun::setBound(int xBound, int yBound) {
	bound[0] = xBound;
	bound[1] = yBound;
}
void Gun::fire(sf::Vector2f nPos, float rot, float speed) {
	//std::cout << "Bullet rotation: " << rot << std::endl;
	//std::cout << "Bullet xSpeed: " << sin(rot) << "\tBullet ySpeed: " << cos(rot) << std::endl;
	for (std::vector<Bullet>::iterator i = bulVect.begin(); i != bulVect.end(); i++) {//Check unused bullets first
		if (!i->getShot()) { //if unused found, use it and don't create a new one.
			i->setPos(nPos);
			i->setRot(rot);
			i->setCurSpeed(-speed*sin(rot*M_PI / 180), speed*cos(rot*M_PI / 180));
			i->setShot(true);
			return;
		}
	}
	float scale = 0.1; //will change to give actual scale later
	Bullet bullet(nPos, scale, bound[0], bound[1], bulText);
	bullet.setRot(rot);
	bullet.setCurSpeed(-speed*sin(rot*M_PI/180), speed*cos(rot*M_PI/180));
	bulVect.push_back(bullet);

}
void Gun::fireCheck() {
	switch (sCase) {
	case 1:
		fireClock.restart();//start timer from 0
		dT = fireClock.getElapsedTime();
		fire(nBulPos, nBulRot, nBulSpeed);
		++sCase;
		break;
	case 2:
		dT = fireClock.getElapsedTime();
		if (dT.asMilliseconds() > minFireTime) { //wait 1/2 second
			sCase = 0; //wait until fireCheck is called again
		}
		break;
	default:
		fireClock.restart();//prevents fireClock from continously building as game progresses
		sCase = 0;//keep sCase 0 unless firing
		break;
	}
}
void Gun::fireCheck(sf::Vector2f nPos, float nRot, float nSpeed, float nMinFireTime) { //Initialize fireCheck() values
	nBulPos = nPos;
	nBulSpeed = nSpeed;
	nBulRot = nRot;
	minFireTime = nMinFireTime;
	sCase = 1;
}
void Gun::main() {
	for (std::vector<Bullet>::iterator i = bulVect.begin(); i != bulVect.end(); i++) {//loop through all bullets
		i->main();
	}
	fireCheck();
}