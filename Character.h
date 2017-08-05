#ifndef CHARACTER_h
#define CHARACTER_h
#include<SFML/Graphics.hpp>
#include "Entity.h"
#include "Gun.h"
class Character : public Entity{
protected:
	Config *cfg;
	Gun *gun;
	float health; //stores health of character 
	float fireTime;
	int gunType; //Used for determining what guntype a character has
public:
	Character();
	Gun &getGun();
	void setGunPulse(int nPulse);
	void setGunFireAngle(float nAngle);
	void damage(int dmg);
	void heal(int heal);
	float getHealth();
	virtual void main();
};


#endif
#pragma once