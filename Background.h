#ifndef BACKGROUND_h
#define BACKGROUND_h

#include <SFML/Graphics.hpp>
#include <vector>

class Background
{
private:
	std::vector<sf::Sprite> backVec;
	sf::Vector2f speed;
	sf::Vector2f pos;
	sf::Vector2f scale;
public:
	Background(sf::Texture &backTexture, float nSpeed, float nPos[2], float scale);
	void setSpeed(float nSpeed);
	void setPos(float nPos[2]);
	void setScale(float nScale);
	void main();
	sf::Vector2f getSpeed();
};

#endif
