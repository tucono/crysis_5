#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include "Config.h"

class TextureManager {
private:
	Config *cfg;
	std::map<std::string, sf::Texture> textMap;
	const std::string errorText = "error";
public:
	TextureManager(Config *nConfig, std::string textFileLoc);
	sf::Texture getTexture(std::string lookup);
};

#endif