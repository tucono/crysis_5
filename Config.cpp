#include <iostream>
#include <ios>
#include <algorithm>
#include <sstream>
#include "Config.h"

Config::Config()
{
	fileLoc = "/home/philip-thomas/Documents/CodeBlocks/Projects/Crysis_5/Assets/Config.txt";
}
Config::Config(std::string nFileLoc) {
	fileLoc = nFileLoc; //set config file location
}
std::string Config::getConfig(std::string lookup, std::string defStr) { //Obtain string in cfg
	std::string line;
	std::string info;
	configIn.open(fileLoc);
	int loc;
	if (configIn.is_open()) {
		std::cout << "File opened. Looking for " << lookup << std::endl;
		while (getline(configIn, line)) {
			if (line.find(lookup) != std::string::npos) { //Found lookup (lookup starts at char 0)
				if (line.find("= ") != std::string::npos) {//Seperate "= " and "="
					loc = line.find("= ");
					loc = loc + 2;
				}
				else {
					loc = line.find("=");
					++loc;
				}
				info = line.substr(loc, line.size() - loc);//get the number after '='
				configIn.close();
				return info;
			}
		}
		configIn.close();//close as input
		std::cout << "String not found. Adding to config file.\n";
		std::cout << "Config file input closed\n";
		configOut.open(fileLoc, std::ios::out | std::ios::app);
		std::cout << "Config file output opened\n";
		configOut << "\n" << lookup << " = " << defStr;
		configOut.close();
		std::cout << "Config file output closed\n";
		//configIn.open(fileLoc);
		//std::cout << "Config file input opened\n";
		return defStr;
	}
	else {
		std::cout << "ERROR: CONFIG FILE NOT FOUND. USING DEFAULT VALUE\n";
	}
	configIn.close();
	return defStr;
}

float Config::getConfig(std::string lookup, float defNum) { //overloaded for float
	std::string line;
	std::string info;
	float num;
	configIn.open(fileLoc);
	if (configIn.is_open()){
		std::cout << "File opened. Looking for " << lookup << std::endl;
		while (getline(configIn, line)) {
			if (line.find(lookup) != std::string::npos) { //Found lookup (lookup starts at char 0)
				line.erase(std::remove(line.begin(), line.end(), ' '), line.end());//remove spaces in string WORKS
				int loc = line.find("=");
				++loc;
				info = line.substr(loc, line.size() - loc);//get the number after '='
				num = strtof((info).c_str(), 0); //convert string number to float number
				configIn.close();
				return num;
			}
		}
		configIn.close();//close as input
		std::cout << "String not found. Adding to config file.\n";
		std::cout << "Config file input closed\n";
		configOut.open(fileLoc, std::ios::out | std::ios::app);
		std::cout << "Config file output opened\n";
		configOut << "\n" << lookup << " = " << defNum;
		configOut.close();
		std::cout << "Config file output closed\n";
		//configIn.open(fileLoc);
		//std::cout << "Config file input opened\n";
		return defNum;
	}
	else{
		std::cout << "ERROR: CONFIG FILE NOT FOUND. USING DEFAULT VALUE\n";
	}
	configIn.close();
	return defNum;
}

int Config::getConfig(std::string lookup, int defNum) { //overloaded for int
	std::string line;
	std::string info;
	std::string::size_type sz;
	int num;
	configIn.open(fileLoc);
	if (configIn.is_open()) {
		std::cout << "File opened. Looking for " << lookup << std::endl;
		while (getline(configIn, line)) {
			if (line.find(lookup) != std::string::npos) { //Found lookup (lookup starts at char 0)
				line.erase(std::remove(line.begin(), line.end(), ' '), line.end());//remove spaces in string WORKS
				int loc = line.find("=");
				++loc;
				info = line.substr(loc, line.size() - loc);//get the number after '='
				num = std::stoi((info).c_str(), &sz); //convert string number to float number
				configIn.close();
				return num;
			}
		}
		configIn.close();//close as input
		std::cout << "String not found. Adding to config file.\n";
		std::cout << "Config file input closed\n";
		configOut.open(fileLoc, std::ios::out | std::ios::app);
		std::cout << "Config file output opened\n";
		configOut << "\n" << lookup << " = " << defNum;
		configOut.close();
		std::cout << "Config file output closed\n";
		//configIn.open(fileLoc);
		//std::cout << "Config file input opened\n";
		return defNum;
	}
	else {
		std::cout << "ERROR: CONFIG FILE NOT FOUND. USING DEFAULT VALUE\n";
	}
	configIn.close();
	return defNum;
}
