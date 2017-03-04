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
	Background(sf::Texture &backTexture, float nSpeed, float nPos[2], float scale);
	void setSpeed(float nSpeed);
	void setPos(float nPos[2]);
	void setScale(float nScale);
	void main();
	sf::Vector2f getSpeed();

	void main()
	{
		if (orient && iter == 0)//if orient = 1, back 1 is on top
		{
			backVec[0].setPosition(0, 0);
			backVec[1].setPosition(0, backVec[0].getSize()); //need to check if works
		}
		else if (!orient && iter == 0//if orient = 0, back 2 is on top
		{

		}
	}
};

#endif
