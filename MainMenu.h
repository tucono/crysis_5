#pragma once
#ifndef MAINMENU_h
#define MAINMENU_h
#include "Menu.h"

class MainMenu : public Menu {
private:
	sf::Event event;
public:
	MainMenu(sf::RenderWindow* nWindow, TextureManager* textMan, int res[2]);
	~MainMenu();
	void init();
	void main();
};

#endif
