#include "Character.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>

Character::Character()
{
}
void Character::setPos(float nxpos, float nypos) //set position of sprite
{
	pos = sf::Vector2f(nxpos, nypos);
	Sprite.setPosition(pos);
}
void Character::setSpeed(float xSpeed, float ySpeed)
{
	speed.x = xSpeed;
	speed.y = ySpeed;
}
void Character::setBound(int xBound, int yBound)
{
	bound[0] = xBound;
	bound[1] = yBound;
}
void Character::setScale(float xScale, float yScale)
{
	scale.x = xScale;
	scale.y = yScale;
}
void Character::setSize(int xSize, int ySize)
{
	size[0] = xSize;
	size[1] = ySize;
}
sf::Vector2f Character::getPos()
{
	return pos;
}
sf::Sprite Character::getSprite()
{
	return Sprite;
}
sf::FloatRect Character::getBoundBox() //access bounding box
{
	return boundBox;
}
int* Character::getSize()
{
	return size;
}
sf::Vector2f Character::getScale()
{
	return scale;
}
void Character::main()
{
}