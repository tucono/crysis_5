#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <vector>
//#include <thread>
#include "Player.h"

Player::Player(float nxpos, float nypos, float nSpeed, float rSpeed, int xBound, int yBound, float scale, float nFireTime, sf::Texture &pTexture, sf::Texture &bTexture){
	pos = sf::Vector2f(nxpos, nypos);
	Sprite.setPosition(pos);//set initial position
	bound[0] = xBound;//set movement boundary in x
	bound[1] = yBound;//set movement boundary in y
	Sprite.setTexture(pTexture);
	setScale(scale, scale);
	boundBox = Sprite.getGlobalBounds();//set bounding box
	setSpeed(nSpeed, nSpeed);
	setRotSpeed(rSpeed);
	setSize();//initialize size[] [only once if size doesn't change]
	gun.setTexture(bTexture);//set bullet textures [WILL BE DONE WITH TEXTURE MANAGER]
	gun.setBound(bound[0], bound[1]);
	Sprite.setOrigin(size[0] / 2, size[1] / 2);
	fireTime = nFireTime;
}
Player::Player(float nxpos, float nypos){ //Testing constructor
	pos = sf::Vector2f(nxpos, nypos);
	Sprite.setColor(sf::Color::Red);
	Sprite.setPosition(pos);
}
void Player::moveCheck() {
	float move[2] = { 0, 0 };
	//Movement Grid
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
		move[0] = speed.x*sin(Sprite.getRotation()*M_PI / 180);
		move[1] = -speed.y*cos(Sprite.getRotation()*M_PI / 180);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
		move[0] = -speed.x*sin(Sprite.getRotation()*M_PI / 180);
		move[1] = speed.y*cos(Sprite.getRotation()*M_PI / 180);
	}
	if (Sprite.getPosition().y > bound[1]) {//too high
		move[1] = 0;
		Sprite.setPosition(Sprite.getPosition().x, bound[1]);
	}
	else if (Sprite.getPosition().y < 0) {//too low
		move[1] = 0;
		Sprite.setPosition(Sprite.getPosition().x, 0);
	}
	if (Sprite.getPosition().x > bound[0] ) {//too far right
		move[0] = 0;
		Sprite.setPosition(bound[0], Sprite.getPosition().y);
	}
	else if (Sprite.getPosition().x < 0) {//too far left
		move[0] = 0;
		Sprite.setPosition(0, Sprite.getPosition().y);
	}
	Sprite.move(move[0], move[1]);
}
void Player::fireCheck(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && gun.getFireCase() == 0) {//only run if spacebar is pressed and 1s have passed since last shot
		//std::cout << "Player rotation: " << Sprite.getRotation() << std::endl;
		gun.fireCheck(Sprite.getPosition(), Sprite.getRotation(), -1, fireTime);

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