//#include "Menu.h"
#include "MainMenu.h"
#include "SFML/Graphics.hpp"
MainMenu::MainMenu(sf::RenderWindow* nWindow, TextureManager* textMan, int res[2]) {
	 //initialize all textures
	nonSelect = textMan->getTexture("buttonOff_01");
	hover = textMan->getTexture("buttonHov_01");
	select = textMan->getTexture("buttonOn_01");
	bgTexture = textMan->getTexture("bg_01");
	if (!buttonFont.loadFromFile("Assets/arial.ttf")) {
		std::cout << "ERROR: BUTTON FONT NOT LOADED\n";
	}
	background = new Background(bgTexture, 0.1f, 0, 0, float(res[1]));
	charSize = 24;//default
	window = nWindow;
	size[0] = 250.f;
	size[1] = 100.f;
	choice = false;
	option = NULL;
	init();
}
MainMenu::~MainMenu() {
	for (std::vector<Button>::size_type t = 0; t < butVector.size(); ++t) {
		delete butVector[t];
	}
}
void MainMenu::init() {
	addButton(24, "Play Game");
	addButton(24, "Settings (Broken)");
	addButton(24, "Quit");
}

void MainMenu::main() {
		window->clear();
		window->draw(background->getSpriteVector()[0]);
		window->draw(background->getSpriteVector()[1]);
		for (std::vector<Button>::size_type t = 0; t < butVector.size(); ++t) {
			choice = butVector[t]->butMain();
			if (choice) {
				option = t + 1;
			}
		}
		background->main();
		window->display();
}
