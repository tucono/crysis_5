#ifndef CHARACTER_h
#define CHARACTER_h

#include<SFML/Graphics.hpp>
class Character
{
protected:
	sf::Vector2f pos;
	sf::Vector2f scale;
	sf::Vector2f speed;
	sf::Sprite Sprite; //Sprite that does all the work
	sf::FloatRect boundBox; //bounding box for sprite
	int bound[2]; //set bounds for enemy
	int size[2]; //stores size of enemy
public:
	Character();
	//Character(float nxpos, float nypos, int xBound, int yBound, int seed, sf::Texture &nTexture);
	//Character(float nxpos, float nypos);
	virtual void main();
	void setPos(float nxpos, float nypos); //set position of sprite
	void setBound(int xBound, int yBound);
	void setSpeed(float xSpeed, float ySpeed);
	void setScale(float xScale, float yScale);
	void setSize(); //may change to int from sf::Vector2f as Sprite doesn't use size
	//void randPos();
	//void randSpeed();
	sf::Vector2f getPos(); //set as pointer to return an array (returns pointer to first el in array); [xpos, ypos]
	sf::Sprite getSprite();
	sf::FloatRect getBoundBox();
	int* getSize();
	sf::Vector2f getScale();
};


#endif
#pragma once
