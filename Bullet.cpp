#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bullet.h"

Bullet::Bullet(sf::Vector2f nPos, float scale, sf::Texture &nTexture){
	Sprite.setTexture(nTexture);//set initial bullet texture
	Sprite.setPosition(nPos);//set initial bullet position
	Sprite.setScale(sf::Vector2f(scale, scale));
	size[0] = Sprite.getGlobalBounds().width;
	size[1] = Sprite.getGlobalBounds().height;
	boundBox = Sprite.getGlobalBounds();
	speed = sf::Vector2f(0,0);
	shot = true;
}

Bullet::Bullet(sf::Vector2f nPos, float scale){
	Sprite.setColor(sf::Color::Green);
	Sprite.setPosition(nPos);
	Sprite.setScale(scale, scale);
	size[0] = Sprite.getGlobalBounds().width;
	size[1] = Sprite.getGlobalBounds().height;
	boundBox = Sprite.getGlobalBounds();
	speed = sf::Vector2f(0, 0);
}

bool Bullet::getShot() {
	return shot;
}

void Bullet::setShot(bool status) {
	shot = status;
}

void Bullet::main(){
	boundBox = Sprite.getGlobalBounds();
	Sprite.move(speed);
	pos = Sprite.getPosition();
	//std::cout << getShot() << "\t" << pos.y << std::endl;
	if (shot) {
		if (getPos().y + size[1] < 0) { //check if out of bounds
			setShot(false);
			setSpeed(0, 0);
			setPos(sf::Vector2f(-100, -100));
		}
	}
}