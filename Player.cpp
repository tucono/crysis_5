#include <cmath>
#include <iostream>
#include <vector>
#include <thread>
#include "Player.h"

Player::Player(float nxpos, float nypos, double nSpeed, int xBound, int yBound, float scale, sf::Texture &pTexture, sf::Texture &bTexture){
	pos = sf::Vector2f(nxpos, nypos);
	bound[0] = xBound;
	bound[1] = yBound;
	Sprite.setTexture(pTexture);
	setScale(scale, scale);
	boundBox = Sprite.getGlobalBounds();//set bounding box
	setSpeed(nSpeed, nSpeed);
	setSize();
	//bulText = bTexture;
	gun.setTexture(bTexture);
}
Player::Player(float nxpos, float nypos){
	pos = sf::Vector2f(nxpos, nypos);
	Sprite.setColor(sf::Color::Red);
	Sprite.setPosition(pos);
}
/*std::vector<Bullet> Player::getBulVect() {
	return pBullets;
}*/
void Player::moveCheck(){ //Movement Grid
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && Sprite.getPosition().x + size[0]< bound[0]){ //check right
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && Sprite.getPosition().y  > 0)//right+up
			Sprite.move(speed.x * 1 / sqrt(2), -speed.y * 1 / sqrt(2));
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && Sprite.getPosition().y + size[1]< bound[1])//right+down
			Sprite.move(speed.x * 1 / sqrt(2), speed.y * 1 / sqrt(2));
		else //only right
			Sprite.move(speed.x, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && Sprite.getPosition().x  > 0){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && Sprite.getPosition().y  > 0)//left+up
			Sprite.move(-speed.x * 1 / sqrt(2), -speed.y * 1 / sqrt(2));
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && Sprite.getPosition().y + size[1] < bound[1])//left+down
			Sprite.move(-speed.x * 1 / sqrt(2), speed.y * 1 / sqrt(2));
		else //only left
			Sprite.move(-speed.x, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && Sprite.getPosition().y + size[1] < bound[1]){
		Sprite.move(0, speed.y);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && Sprite.getPosition().y  > 0){
		Sprite.move(0, -speed.y);
	}
}
void Player::fireCheck() { //should be in seperate thread
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sCase == 0) {//only run if spacebar is pressed and 1s have passed since last shot
		sCase = 1;
	}
	switch (sCase) {
	case 1: 
		std::cout << "Initialize firing\n";
		fireClock.restart();//start timer from 0
		dT = fireClock.getElapsedTime();
		gun.fire(Sprite.getPosition(), 1);//will do this many times in one press
		//fire();
		++sCase;
		break;
	case 2:
		dT = fireClock.getElapsedTime();
		if (dT.asMilliseconds() > 500) { //wait 1/2 second
			sCase = 0;
			std::cout << "Can fire again\n";
		}
		break;
	default: 
		fireClock.restart();//prevents fireClock from continously building as game progresses
		sCase = 0;//keep sCase 0 unless firing
		break;
	}
}
Gun &Player::getGun()
{
	return gun;
}
void Player::main(){
	boundBox = Sprite.getGlobalBounds();
	pos = Sprite.getPosition();
	moveCheck();
	fireCheck();
	gun.main();
}