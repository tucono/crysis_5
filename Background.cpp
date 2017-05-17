#include "Background.h"
//#include <iostream> //DEBUGGING PURPOSES ONLY
#include <vector>

Background::Background(sf::Texture &backTexture, float nSpeed, float xPos, float yPos, float windowHeight){
	sf::Sprite sprite1; sf::Sprite sprite2;
	backVec.push_back(sprite1);
	backVec.push_back(sprite2);
	for (std::vector<sf::Sprite>::iterator i = backVec.begin(); i != backVec.end(); ++i){ //set textures/positions 
		i->setTexture(backTexture);
		i->setPosition(sf::Vector2f(xPos, yPos));
	}
	float nScale = windowHeight / backVec[0].getGlobalBounds().height; //set background to window height
	setScale(nScale);
	speed = sf::Vector2f(0, nSpeed);
	init = false;
	//orient = 1;
}

void Background::setPos(float nPos[2]){
	pos = sf::Vector2f(nPos[1], nPos[2]);
}
void Background::setSpeed(float nSpeed){
	speed.y = nSpeed;
}
void Background::setScale(float nScale){
	scale.x = nScale;
	scale.y = nScale;
	for (std::vector<sf::Sprite>::iterator i = backVec.begin(); i != backVec.end(); ++i){
		i->setScale(scale.x, scale.y);
	}
}
std::vector<sf::Sprite> Background::getSpriteVector(){
	return backVec;
}
sf::Sprite Background::getSprite(std::vector<sf::Sprite>::size_type i){
	return backVec[i];
}
sf::Vector2f Background::getSpeed(){
	return speed;
}
void Background::main(){
	if (!init) {//initialization of background
		backVec[0].setPosition(0, 0);
		backVec[1].setPosition(0, -backVec[0].getGlobalBounds().height); //attachment works
		init = true;
	}
	if (backVec[0].getPosition().y > backVec[0].getGlobalBounds().height) {
		backVec[0].setPosition(0, -backVec[1].getGlobalBounds().height); //once it goes below screen, set on top of background 1
	}
	if (backVec[1].getPosition().y > backVec[1].getGlobalBounds().height) {
		backVec[1].setPosition(0, -backVec[0].getGlobalBounds().height); //once below screen, set on top of background 2
	}
	backVec[0].move(speed);
	backVec[1].move(speed);
}