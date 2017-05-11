#include <SFML/Graphics.hpp>
#include "Bullet.h"

Bullet::Bullet(sf::Vector2f nPos, float scale, sf::Texture &nTexture){
	Sprite.setTexture(nTexture);
	Sprite.setPosition(nPos);
	Sprite.setScale(sf::Vector2f(scale, scale));
	size[0] = Sprite.getGlobalBounds().width;
	size[1] = Sprite.getGlobalBounds().height;
	boundBox = Sprite.getGlobalBounds();
	speed = sf::Vector2f(0,0);
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

void Bullet::main(){
	boundBox = Sprite.getGlobalBounds();
	Sprite.move(speed);
}