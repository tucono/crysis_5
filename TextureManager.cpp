#include "TextureManager.h"
#include <iostream>

TextureManager::TextureManager(Config *nConfig, std::string textFileLoc) {
	cfg = nConfig;
	//Load Background textures
	if (!textMap["bg_01"].loadFromFile(cfg->getConfig("bgTextureLoc", textFileLoc + "Space.png"))) {
		std::cout << "ERROR IN BACKGROUND TEXTURE LOADING\n";
	}

	//Load player textures
	if (!textMap["player_01"].loadFromFile(cfg->getConfig("plTextureLoc", textFileLoc + "playerChar.png"))) {
		std::cout << "ERROR IN PLAYER TEXTURE LOADING\n";
	}

	//Load enemy textures
	if(!textMap["enemy_01"].loadFromFile(cfg->getConfig("enTextureLoc", textFileLoc + "koreaEnemy.png"))){
		std::cout << "ERROR IN ENEMY TEXTURE LOADING\n";
	}

	//Load bullet textures
	if (!textMap["bul_01"].loadFromFile(cfg->getConfig("bulTextureLoc", textFileLoc + "laser.png"))) {
		std::cout << "ERROR IN BULLET TEXTURE LOADING\n";
	}

	//Load error texture
	if (!textMap[errorText].loadFromFile(cfg->getConfig("erTextLoc", textFileLoc + "Error.png"))) {
		std::cout << "ERROR IN ERROR TEXTURE LOADING\n";
	}
}

sf::Texture TextureManager::getTexture(std::string lookup) {
	//sf::Texture text;
	try {
		return textMap.at(lookup);
	}
	catch (const std::out_of_range& e) {
		std::cout << "ERROR: " << lookup << "NOT FOUND IN TEXTUREMANAGER\n";
	}
	catch (...) {
		std::cout << "ERROR IN TEXTUREMANAGER\n";
	}
	return textMap.at(errorText);
}