#ifndef CONFIG_h
#define CONFIG_h
#include <fstream>
#include <string>
class Config
{
private:
	std::ofstream configFile;
public:
	Config(std::string fileLoc);
	std::string getConfig(std::string lookup);
	void close();
};


#endif
