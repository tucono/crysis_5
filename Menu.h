#pragma once
#ifndef MENU_h
#define MENU_h
#include<vector>
#include "SFML/Graphics.hpp"
#include "TextureManager.h"
#include "Button.h"
#include "Background.h"

class Menu {
protected:
	std::vector<Button*> butVector;
	sf::Texture nonSelect;
	sf::Texture hover;
	sf::Texture select;
	sf::Texture bgTexture;
	Background *background;
	sf::Font buttonFont;
	sf::RenderWindow* window;
	unsigned int charSize;
	unsigned int option;
	bool choice;
	float size[2];//button sizes
public:
	//Menu(sf::RenderWindow* nWindow, TextureManager* textMan, float nSize[2]);//initialize all textures
	//~Menu();
	unsigned int getOption();
	void addButton(unsigned int nCharSize, std::string nButtonStr);
	virtual void main() = 0; //ABSTRACT CLASS NOW
};


#endif