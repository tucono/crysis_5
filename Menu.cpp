#include "Menu.h"

/*Menu::Menu(sf::RenderWindow* nWindow, TextureManager* textMan, float nSize[2]) {//initialize all textures
	this->nonSelect = &(textMan->getTexture("buttonOff_01"));
	this->hover = &(textMan->getTexture("buttonHov_01"));
	this->select = &(textMan->getTexture("buttonOn_01"));
	charSize = 24;//default
	window = nWindow;
	*size = *nSize;
	choice = false;
	option = NULL;
}
Menu::~Menu() {
	for (std::vector<Button>::size_type t = 0; t < butVector.size(); ++t) {
		delete butVector[t];
	}
}*/
void Menu::addButton(unsigned int nCharSize, std::string nButtonStr) {
	if (butVector.size() == 0) {
		butVector.push_back(new Button(window, &nonSelect, &hover, &select, &buttonFont, charSize, nButtonStr, size, sf::Vector2f(100.0f, 100.0f)));
		std::cout << "button1 pos = " << butVector[0]->getPos().x << ", " << butVector[0]->getPos().y << "\n";
	}
	else {
		sf::Vector2f lastPos = butVector[butVector.size() - 1]->getPos();
		std::cout << "LastPos.x = " << lastPos.x << "\tlastPos.y = " << lastPos.y << "\n";
		butVector.push_back(new Button(window, &nonSelect, &hover, &select, &buttonFont, charSize, nButtonStr, size, sf::Vector2f(lastPos.x, lastPos.y+200)));
	}
}
unsigned int Menu::getOption() {
	return option;
}