#include "Entity.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>

Entity::Entity() {}
void Entity::setPos(sf::Vector2f nPos) { //set position of character
											//pos = sf::Vector2f(nxpos, nypos);
	Sprite.setPosition(nPos);
}
void Entity::setCurSpeed(float xSpeed, float ySpeed) {
	curSpeed = sf::Vector2f(xSpeed, ySpeed);
}
void Entity::setMaxSpeed(float nMaxSpeed) {
	maxSpeed = nMaxSpeed;
}
void Entity::setSpeedMod(float nSpeedMod) {
	speedMod = nSpeedMod;
}
void Entity::setRot(float rot) {
	Sprite.setRotation(rot);
}
void Entity::setRotSpeed(float speed) {
	rotSpeed = speed;
}
void Entity::setBound(int xBound, int yBound) {
	bound[0] = xBound;
	bound[1] = yBound;
}
void Entity::setScale(float xScale, float yScale) {
	scale.x = xScale;
	scale.y = yScale;
	Sprite.setScale(scale);
}
/*void Entity::setSize() {
	size[0] = Sprite.getGlobalBounds().width;
	size[1] = Sprite.getGlobalBounds().height;
}*/
sf::Vector2f Entity::getPos() {
	return Sprite.getPosition();
}
sf::Sprite Entity::getSprite() {
	return Sprite;
}
sf::FloatRect Entity::getBoundBox() {
	return boundBox;
}
float* Entity::getSize() {
	size[0] = Sprite.getGlobalBounds().width;
	size[1] = Sprite.getGlobalBounds().height;
	return size;
}
sf::Vector2f Entity::getScale() {
	return Sprite.getScale();
}
void Entity::main() {}