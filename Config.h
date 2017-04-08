#ifndef CONFIG_h
#define CONFIG_h
#include <fstream>
#include <string>
class Config{
private:
	std::ifstream configIn;
	std::ofstream configOut;
	std::string fileLoc;
public:
	Config(std::string nFileLoc);
	std::string getConfigString(std::string lookup, std::string default);
	float getConfigFloat(std::string lookup, float defNum);
	//void close();
};
#endif
