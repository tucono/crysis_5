#pragma once
#ifndef ENTITY_h
#define ENTITY_h
#include <SFML/Graphics.hpp>
class Entity {
protected:
	sf::Vector2f pos;
	sf::Vector2f scale;
	sf::Vector2f curSpeed;
	sf::Sprite Sprite; //Sprite that does all the work
	sf::FloatRect boundBox; //bounding box for sprite
	float rotSpeed;
	float maxSpeed;
	float speedMod; //must be between 0 and 1
	int bound[2]; //set bounds for character
	float size[2]; //stores size of character
public:
	Entity();
	virtual void main();
	void setPos(sf::Vector2f nPos); //set position of sprite
	void setBound(int xBound, int yBound);
	void setCurSpeed(float xSpeed, float ySpeed);
	void setMaxSpeed(float nMaxSpeed);
	void setSpeedMod(float nSpeedMod);
	void setRot(float rot);
	void setRotSpeed(float speed);
	void setScale(float xScale, float yScale);
	void setSize(); //may change to int from sf::Vector2f as Sprite doesn't use size
	sf::Vector2f getPos();
	sf::Sprite getSprite();
	sf::FloatRect getBoundBox();
	float* getSize();
	sf::Vector2f getScale();
};

#endif