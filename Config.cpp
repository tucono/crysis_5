#include <iostream>
#include "Config.h"

Config::Config(std::string fileLoc) {
	configFile.open(fileLoc);
	if (configFile.is_open())
		std::cout << "Config File Loaded\n";
	else
		std::cout << "ERROR OPENING CONFIG FILE. Using Default Values\n";
}

std::string Config::getConfig(std::string lookup) {
	std::string line;
	if(configFile.is_open()){
		while(getline(configFile, line)){
			if (line.find(lookup)) { //Found lookup, set string to after =
				std::cout << "found\n";
			}
		}
	}
}