#include "Character.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>

Character::Character(){}
void Character::setPos(sf::Vector2f nPos){ //set position of character
	//pos = sf::Vector2f(nxpos, nypos);
	Sprite.setPosition(nPos);
}
void Character::setCurSpeed(float xSpeed, float ySpeed) {
	curSpeed = sf::Vector2f(xSpeed, ySpeed);
}
void Character::setMaxSpeed(float nMaxSpeed){
	maxSpeed = nMaxSpeed;
}
void Character::setSpeedMod(float nSpeedMod) {
	speedMod = nSpeedMod;
}
void Character::setRot(float rot) {
	Sprite.setRotation(rot);
}
void Character::setRotSpeed(float speed) {
	rotSpeed = speed;
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
void Character::damage(int dmg) {
	health -= dmg;
}
void Character::heal(int heal) {
	health += heal;
}
int Character::getHealth() {
	return health;
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