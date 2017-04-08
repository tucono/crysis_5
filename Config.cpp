#include <iostream>
#include <algorithm>
#include "Config.h"

Config::Config(std::string nFileLoc) {
	fileLoc = nFileLoc; //set config file location
}

float Config::getConfigFloat(std::string lookup, float defNum) {
	std::string line;
	std::string info;
	float num;
	bool addToCfg = 0;
	configIn.open(fileLoc);
	if (configIn.is_open()){ 
		std::cout << "File opened\n";
		while (getline(configIn, line)) {
			line.erase(std::remove(line.begin(), line.end(), ' '), line.end());//remove spaces in string WORKS
			std::cout << line << std::endl;
			if (line.find(lookup) != std::string::npos) { //Found lookup (lookup starts at char 0)
				int loc = line.find("=");
				++loc;
				std::cout << line.substr(loc, line.size() - loc)<<std::endl; //not working
				info = line.substr(loc, line.size() - loc);//get the number after '='
				num = strtof((info).c_str(), 0); //convert string number to float number
				return num;
			}
			else { //String not found. Add to config file
				addToCfg = 1;
			}
		}
		if (addToCfg) {//If not found, add at the end
			configIn.close();//close as input
			std::cout << "String not found. Adding to config file.\n";
			std::cout << "Config file input closed\n";
			configOut.open(fileLoc);
			std::cout << "Config file output opened\n";
			configOut << lookup << " = ";
			configOut.close();
			std::cout << "Config file output closed\n";
			configIn.open(fileLoc);
			std::cout << "Config file input opened\n";
			return defNum;
		}
		configIn.close();
	}
	else{
		std::cout << "ERROR: CONFIG FILE NOT FOUND. USING DEFAULT VALUE\n";
	}
	return defNum;
}