#ifndef PLAYER_h
#define PLAYER_h
#include <SFML/Graphics.hpp>
#include "Character.h"

class Player : public Character{
private:

public:
	Player(float nxpos, float nypos, float nSpeed, int xbound, int ybound, float scale, sf::Texture &nTexture);
	Player(float nxpos, float nypos);
	void moveCheck();
	void main();
};

#endif