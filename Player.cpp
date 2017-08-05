#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <vector>
//#include <thread>
#include "Player.h"

Player::Player(float nxpos, float nypos, float nSpeed, float rSpeed, float nSpeedMod, int xBound, int yBound, float scale, float nFireTime, int nGunType, sf::Texture &pTexture, sf::Texture &bTexture, Config *nCfg){
	//pos = sf::Vector2f(nxpos, nypos);
	Sprite.setPosition(sf::Vector2f(nxpos, nypos));//set initial position
	bound[0] = xBound;//set movement boundary in x
	bound[1] = yBound;//set movement boundary in y
	Sprite.setTexture(pTexture);
	setScale(scale, scale);
	boundBox = Sprite.getGlobalBounds();//set bounding box
	setMaxSpeed(nSpeed);
	setCurSpeed(0, 0);
	setRotSpeed(rSpeed);
	//setSize();//initialize size[] [only once if size doesn't change]
	gun = new Gun(nGunType, nCfg);
	gun->setTexture(bTexture);//set bullet textures [WILL BE DONE WITH TEXTURE MANAGER]
	gun->setBound(bound[0], bound[1]);
	Sprite.setOrigin(size[0] / 2, size[1] / 2);
	fireTime = nFireTime;
	health = 100;
	//speedMod = 0.0001;
	speedMod = nSpeedMod;
	score = 0;
	setGunPulse(1);//default gun pulse of 1
	gun->setFireAngle(0);//default fireAngle
}
Player::~Player() {
	delete gun;
}
int Player::getScore() {
	return score;
}
void Player::moveCheck() {
	//float move[2] = { 0, 0 };
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && Sprite.getPosition().x + size[0]< bound[0]){ //check right
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && Sprite.getPosition().y  > 0)//right+up
			Sprite.move(speed.x * 1 / float(sqrt(2)), -speed.y * 1 / float(sqrt(2)));
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && Sprite.getPosition().y + size[1]< bound[1])//right+down
			Sprite.move(speed.x * 1 / float(sqrt(2)), speed.y * 1 / float(sqrt(2)));
		else //only right
			Sprite.move(speed.x, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && Sprite.getPosition().x  > 0){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && Sprite.getPosition().y  > 0)//left+up
			Sprite.move(-speed.x * 1 / float(sqrt(2)), -speed.y * 1 / float(sqrt(2)));
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && Sprite.getPosition().y + size[1] < bound[1])//left+down
			Sprite.move(-speed.x * 1 / float(sqrt(2)), speed.y * 1 / float(sqrt(2)));
		else //only left
			Sprite.move(-speed.x, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && Sprite.getPosition().y + size[1] < bound[1]){
		Sprite.move(0, speed.y);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && Sprite.getPosition().y  > 0){
		Sprite.move(0, -speed.y);
	}*/
	//Turning
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		Sprite.rotate(rotSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		Sprite.rotate(-rotSpeed);
	}
	// Movement Grid
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) { //accelerate player forward
		if (abs(sqrt(curSpeed.x*curSpeed.x + curSpeed.y*curSpeed.y)) < maxSpeed) {
			//std::cout << "Player up increasing. CurSpeed: " << curSpeed.x << " " << curSpeed.y << std::endl;
			setCurSpeed(curSpeed.x + speedMod*float(sin(Sprite.getRotation()*M_PI / 180)), curSpeed.y - speedMod*float(cos(Sprite.getRotation()*M_PI / 180)));
		}
		else
		{
			//std::cout << "Player up max. CurSpeed: " << curSpeed.x << " " << curSpeed.y << std::endl;
			setCurSpeed(maxSpeed*float(sin(Sprite.getRotation()*M_PI / 180)), -maxSpeed*float(cos(Sprite.getRotation()*M_PI / 180)));
		}
		//curSpeed.x = maxSpeed*sin(Sprite.getRotation()*M_PI / 180);
		//curSpeed.y = -maxSpeed*cos(Sprite.getRotation()*M_PI / 180);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) { //accelerate player backward
		if (abs(sqrt(curSpeed.x*curSpeed.x + curSpeed.y*curSpeed.y)) < maxSpeed) {
			setCurSpeed(curSpeed.x - speedMod*float(sin(Sprite.getRotation()*M_PI / 180)), curSpeed.y + speedMod*float(cos(Sprite.getRotation()*M_PI / 180)));
		}
		else
		{
			setCurSpeed(-maxSpeed*float(sin(Sprite.getRotation()*M_PI / 180)), maxSpeed*float(cos(Sprite.getRotation()*M_PI / 180)));
		}
		//setCurSpeed(-maxSpeed*sin(Sprite.getRotation()*M_PI / 180), maxSpeed*cos(Sprite.getRotation()*M_PI / 180));
		//curSpeed.x = -maxSpeed*sin(Sprite.getRotation()*M_PI / 180);
		//curSpeed.y = maxSpeed*cos(Sprite.getRotation()*M_PI / 180);
	}
	else { //decelerate player
		if (curSpeed.x > 0) {
			setCurSpeed(curSpeed.x - speedMod/5, curSpeed.y);
		}
		else if (curSpeed.x < 0){
			setCurSpeed(curSpeed.x + speedMod/5, curSpeed.y);
		}
		if (curSpeed.y > 0) {
			setCurSpeed(curSpeed.x, curSpeed.y - speedMod/5);
		}
		else if (curSpeed.y < 0) {
			setCurSpeed(curSpeed.x, curSpeed.y + speedMod/5);
		}
	}
	if (Sprite.getPosition().y > bound[1]) {//too high
		setCurSpeed(curSpeed.x, 0);
		Sprite.setPosition(Sprite.getPosition().x, float(bound[1]));
	}
	else if (Sprite.getPosition().y < 0) {//too low
		setCurSpeed(curSpeed.x, 0);
		Sprite.setPosition(Sprite.getPosition().x, 0);
	}
	if (Sprite.getPosition().x > bound[0] ) {//too far right
		setCurSpeed(0, curSpeed.y);
		//move[0] = 0;
		Sprite.setPosition(float(bound[0]), Sprite.getPosition().y);
	}
	else if (Sprite.getPosition().x < 0) {//too far left
		setCurSpeed(0, curSpeed.y);
		//move[0] = 0;
		Sprite.setPosition(0, Sprite.getPosition().y);
	}
	Sprite.move(curSpeed);
}
void Player::fireCheck(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && gun->getFireCase() == 0) {//only run if spacebar is pressed and 1s have passed since last shot
		//std::cout << "Player rotation: " << Sprite.getRotation() << std::endl;
		gun->fireCheck(Sprite.getPosition(), Sprite.getRotation(), -1, fireTime);

	}
}
void Player::addScore(int addScore) {
	score += addScore;
}
void Player::main(){
	boundBox = Sprite.getGlobalBounds();
	//pos = Sprite.getPosition();
	moveCheck();
	fireCheck();
	gun->main();
}