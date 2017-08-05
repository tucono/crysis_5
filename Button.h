#pragma once
#ifndef BUTTON_h
#define BUTTON_h
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Button : public Entity {
private:
	sf::RenderWindow *window;
	sf::Texture *nonSelect;
	sf::Texture *hover;
	sf::Texture *select;
	sf::Font *buttonFont;
	sf::Text buttonText;
	unsigned int charSize;
	std::string buttonStr;
	int xBound[2];
	int yBound[2];
public:
	Button(sf::RenderWindow *nWindow, sf::Texture *nNonSelect, sf::Texture *nHover, sf::Texture *nSelect, sf::Font *nButtonFont, unsigned int nCharSize, std::string nButtonStr, float size[2], sf::Vector2f position);
	void setButtonText(std::string nButtonStr);
	void setButtonFont(sf::Font *nButtonFont);
	void setCharSize(int nCharSize);
	void setNonSelect();
	void setHover();
	void setSelect();
	sf::Text getText();
	bool getClick();
	bool butMain();
};


#endif