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
	nPulse = 1;//default
	fireAngle = 0;//default
}
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
void Gun::setN_Pulse(int newPulse) {
	nPulse = newPulse;
}
void Gun::setFireAngle(float nAngle) {
	fireAngle = nAngle;
}
void Gun::fire(sf::Vector2f nPos, float rot, float speed) {
	//std::cout << "Bullet rotation: " << rot << std::endl;
	//std::cout << "Bullet xSpeed: " << sin(rot) << "\tBullet ySpeed: " << cos(rot) << std::endl;
	for (std::vector<Bullet>::iterator i = bulVect.begin(); i != bulVect.end(); i++) {//Check unused bullets first
		if (!i->getShot()) { //if unused found, use it and don't create a new one.
			i->setPos(nPos);
			i->setRot(rot);
			i->setCurSpeed(-speed*float(sin(rot*M_PI / 180)), float(speed*cos(rot*M_PI / 180)));
			i->setShot(true);
			return;
		}
	}
	float scale = 0.1f; //will change to give actual scale later
	Bullet bullet(nPos, scale, bound[0], bound[1], bulText);
	bullet.setRot(rot);
	bullet.setCurSpeed(-speed*float(sin(rot*M_PI/180)), speed*float(cos(rot*M_PI/180)));
	bulVect.push_back(bullet);

}
void Gun::pulseFire() {
	switch (sCase) {
	case 1:
		fireClock.restart();//start timer from 0
		//std::cout << "in pulseFire() - Pulse = " << nPulse << std::endl;
		dT = fireClock.getElapsedTime();
		for (int i = 0; i < nPulse; ++i) {
			//std::cout << "Pulse Rot " << i << " = " << nBulRot + i * 360 / float(nPulse) << std::endl;
			fire(nBulPos, nBulRot+i*360/float(nPulse), nBulSpeed);//will pulse radially from origin
		}
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

void Gun::pulseAngleFire() {
	float startAngle = nBulRot - fireAngle / 2;//First angle that bullet will be shot at
	switch (sCase) {
	case 1:
		fireClock.restart();//start timer from 0
		//std::cout << "in pulseAngleFire() - Pulse = " << nPulse << std::endl;
		dT = fireClock.getElapsedTime();
		for (int i = 0; i < nPulse; ++i) {
			//std::cout << "Pulse Rot " << i << " = " << nBulRot + i * 360 / float(nPulse) << std::endl;
			fire(nBulPos, startAngle + i * fireAngle / float(nPulse), nBulSpeed);//will pulse radially from origin
		}
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
void Gun::main(int gunType) {
	for (std::vector<Bullet>::iterator i = bulVect.begin(); i != bulVect.end(); i++) {//loop through all bullets
		i->main();
	}
	switch (gunType) {
	case 0: //pulse. nPulse determines number of shots, equidistant radial from character.
		pulseFire();
		break;
	case 1://pulse. nPulse determines number of shots, angle determines spread
		pulseAngleFire();
		break;
	default:
		setN_Pulse(1);//constant stream of pulse of 1
		pulseFire();
		break;
	}
}