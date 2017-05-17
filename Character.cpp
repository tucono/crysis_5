#include "Character.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>

Character::Character(){}
void Character::setPos(sf::Vector2f nPos){ //set position of character
	//pos = sf::Vector2f(nxpos, nypos);
	Sprite.setPosition(nPos);
}
void Character::setSpeed(float xSpeed, float ySpeed){
	speed.x = xSpeed;
	speed.y = ySpeed;
}
void Character::setBound(int xBound, int yBound){
	bound[0] = xBound;
	bound[1] = yBound;
}
void Character::setScale(float xScale, float yScale){
	scale.x = xScale;
	scale.y = yScale;
	Sprite.setScale(scale);
}
void Character::setSize(){
	size[0] = Sprite.getGlobalBounds().width;
	size[1] = Sprite.getGlobalBounds().height;
}
sf::Vector2f Character::getPos(){
	return pos;
}
sf::Sprite Character::getSprite(){
	return Sprite;
}
sf::FloatRect Character::getBoundBox(){
	return boundBox;
}
float* Character::getSize(){
	return size;
}
sf::Vector2f Character::getScale(){
	return scale;
}
void Character::main(){}