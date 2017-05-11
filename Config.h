#ifndef CONFIG_h
#define CONFIG_h
#include <fstream>
#include <string>
class Config{
private:
	std::ifstream configIn;
	std::fstream configOut;
	std::string fileLoc;
public:
	Config();
	Config(std::string nFileLoc);
	std::string getConfig(std::string lookup, std::string defStr);
	float getConfig(std::string lookup, float defNum);
	int getConfig(std::string lookup, int defNum);
	//void close();
};
#endif
