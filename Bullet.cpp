//#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bullet.h"

Bullet::Bullet(sf::Vector2f nPos, float scale, int xBound, int yBound, sf::Texture &nTexture){
	Sprite.setTexture(nTexture);//set initial bullet texture
	Sprite.setPosition(nPos);//set initial bullet position
	Sprite.setScale(sf::Vector2f(scale, scale));
	size[0] = Sprite.getGlobalBounds().width;
	size[1] = Sprite.getGlobalBounds().height;
	boundBox = Sprite.getGlobalBounds();
	bound[0] = xBound;
	bound[1] = yBound;
	curSpeed = sf::Vector2f(0,0);
	shot = true;
}

Bullet::Bullet(sf::Vector2f nPos, float scale){
	Sprite.setColor(sf::Color::Green);
	Sprite.setPosition(nPos);
	Sprite.setScale(scale, scale);
	size[0] = Sprite.getGlobalBounds().width;
	size[1] = Sprite.getGlobalBounds().height;
	boundBox = Sprite.getGlobalBounds();
	curSpeed = sf::Vector2f(0, 0);
}

bool Bullet::getShot() {
	return shot;
}

void Bullet::setShot(bool status) {
	shot = status;
}

void Bullet::main(){
	boundBox = Sprite.getGlobalBounds();
	Sprite.move(curSpeed);
	//pos = Sprite.getPosition();
	//std::cout << getShot() << "\t" << pos.y << std::endl;
	if (shot) {
		if (getPos().y < 0 || getPos().y > bound[1]+size[1] || getPos().x < 0 || getPos().x > bound[0]) { //check if out of bounds
			//std::cout << "Bullet Pos: " << Sprite.getPosition().x << "," << Sprite.getPosition().y << std::endl;
			//std::cout << "Bullet Reset" << std::endl;
			setShot(false);
			setCurSpeed(0, 0);
			setPos(sf::Vector2f(-100, -100));
		}
	}
}