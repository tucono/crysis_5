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
	sf::Vector2f origin; //set size of window
	bool orient; int iter;
public:
	Background(sf::Texture &backTexture, float nSpeed, float xPos, float yPos, float windowHeight);
	void setPos(float nPos[2]);
	void setSpeed(float nSpeed);
	void setScale(float nScale);
	void flipOrient();
	void resetIter();
	std::vector<sf::Sprite> getSpriteVector();
	sf::Sprite getSprite(std::vector<sf::Sprite>::size_type i);
	sf::Vector2f getSpeed();
	bool getOrient();
	void main();

};

#endif
