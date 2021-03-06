#ifndef GUN_h
#define GUN_h
#include <vector>
#include <SFML/Graphics.hpp>
#include "Config.h"
#include "Bullet.h"

class Gun {
private:
	Config cfg;
	std::vector<Bullet> bulVect;
	sf::Texture bulText;
	sf::Clock fireClock;
	sf::Time dT;
	sf::Vector2f nBulPos;
	float nBulSpeed;
	float nBulRot;
	float minFireTime;
	float fireAngle;
	int sCase;
	int bound[2];
	int nPulse; //Number of pulses fired for pulse gun
public:
	Gun();
	//Gun(const Gun&) = default;
	//Gun& operator =(const Gun& other);
	std::vector<Bullet> &getBulVect();
	int getFireCase();
	void setTexture(sf::Texture& nText);
	void setBound(int xBound, int yBound);
	void setN_Pulse(int newPulse);
	void setFireAngle(float nAngle);
	void fire(sf::Vector2f nPos, float rot, float speed);
	void pulseFire();//pulse w/ nPulse shots equidistant radially
	void pulseAngleFire();//pulse w/ nPulse shots equidistant with fireAngle spread
	void fireCheck(sf::Vector2f nPos, float nRot, float nSpeed, float nMinFireTime);
	void main(int gunType);//gunType will determine how the bullets are fired (pulse, beam, etc.)
};
#endif