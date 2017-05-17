#include <cmath>
#include <iostream>
#include <vector>
//#include <thread>
#include "Player.h"

Player::Player(float nxpos, float nypos, float nSpeed, int xBound, int yBound, float scale, sf::Texture &pTexture, sf::Texture &bTexture){
	pos = sf::Vector2f(nxpos, nypos);
	Sprite.setPosition(pos);//set initial position
	bound[0] = xBound;//set movement boundary in x
	bound[1] = yBound;//set movement boundary in y
	Sprite.setTexture(pTexture);
	setScale(scale, scale);
	boundBox = Sprite.getGlobalBounds();//set bounding box
	setSpeed(nSpeed, nSpeed);
	setSize();//initialize size[] [only once if size doesn't change]
	gun.setTexture(bTexture);//set bullet textures [WILL BE DONE WITH TEXTURE MANAGER]
}
Player::Player(float nxpos, float nypos){ //Testing constructor
	pos = sf::Vector2f(nxpos, nypos);
	Sprite.setColor(sf::Color::Red);
	Sprite.setPosition(pos);
}
void Player::moveCheck(){ //Movement Grid
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && Sprite.getPosition().x + size[0]< bound[0]){ //check right
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && Sprite.getPosition().y  > 0)//right+up
			Sprite.move(speed.x * 1 / float(sqrt(2)), -speed.y * 1 / float(sqrt(2)));
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && Sprite.getPosition().y + size[1]< bound[1])//right+down
			Sprite.move(speed.x * 1 / float(sqrt(2)), speed.y * 1 / float(sqrt(2)));
		else //only right
			Sprite.move(speed.x, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && Sprite.getPosition().x  > 0){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && Sprite.getPosition().y  > 0)//left+up
			Sprite.move(-speed.x * 1 / float(sqrt(2)), -speed.y * 1 / float(sqrt(2)));
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && Sprite.getPosition().y + size[1] < bound[1])//left+down
			Sprite.move(-speed.x * 1 / float(sqrt(2)), speed.y * 1 / float(sqrt(2)));
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
void Player::fireCheck(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && gun.getFireCase() == 0) {//only run if spacebar is pressed and 1s have passed since last shot
		gun.fireCheck(Sprite.getPosition(), -1);
	}
}
Gun &Player::getGun(){
	return gun;
}
void Player::main(){
	boundBox = Sprite.getGlobalBounds();
	pos = Sprite.getPosition();
	moveCheck();
	fireCheck();
	gun.main();
}