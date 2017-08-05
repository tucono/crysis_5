#include "TextureManager.h"
#include <iostream>

TextureManager::TextureManager(Config *nConfig, std::string nTextFileLoc) {
	cfg = nConfig;
	textFileLoc = nTextFileLoc;
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

	//Load Button Textures
	if (!textMap["buttonHov_01"].loadFromFile(cfg->getConfig("butHovTextureLoc_01", textFileLoc + "butHover_01.png"))) {
		std::cout << "ERROR IN BUTTON_HOVER TEXTURE LOADING\n";
	}

	if (!textMap["buttonOn_01"].loadFromFile(cfg->getConfig("butOnTextureLoc_01", textFileLoc + "butOn_01.png"))) {
		std::cout << "ERROR IN BUTTON_ON TEXTURE LOADING\n";
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
	catch (const std::out_of_range& e) {//Not found in original array. Adding from base texture file location
		std::cout << "ERROR: " << lookup << "NOT FOUND IN TEXTUREMANAGER\tChecking in " << textFileLoc << std::endl;
		if (!textMap[lookup].loadFromFile(textFileLoc + lookup + ".png")) {
			std::cout << "ERROR:" << lookup << "NOT FOUND IN " << textFileLoc << std::endl;//Lookup.png was not found in texture file location. Return error texture
			return textMap.at(errorText);
		}
		return textMap.at(lookup);//Lookup.png found. Return texture
	}
	catch (...) {
		std::cout << "ERROR IN TEXTUREMANAGER\n";
	}
	return textMap.at(errorText);
}