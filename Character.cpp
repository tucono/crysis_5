#include "Character.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>

Character::Character(){}
void Character::damage(int dmg) {
	health -= dmg;
}
void Character::heal(int heal) {
	health += heal;
}
float Character::getHealth() {
	return health;
}
void Character::setGunPulse(int nPulse) {
	gun->setN_Pulse(nPulse);
}
void Character::setGunFireAngle(float nAngle) {
	gun->setFireAngle(nAngle);
}
Gun &Character::getGun() {
	return *gun;
}
void Character::main(){}