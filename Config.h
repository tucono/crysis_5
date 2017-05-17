#ifndef CONFIG_h
#define CONFIG_h
#include <fstream>
#include <string>
class Config{
private:
	std::ifstream configIn; //for reading cfg
	std::fstream configOut; //for writing to cfg
	std::string fileLoc;
public:
	Config();
	Config(std::string nFileLoc);
	//Config& operator=(const Config& other);
	std::string getConfig(std::string lookup, std::string defStr);
	float getConfig(std::string lookup, float defNum);
	int getConfig(std::string lookup, int defNum);
};
#endif
