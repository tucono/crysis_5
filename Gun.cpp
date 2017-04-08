#include "Gun.h"
#include "Bullet.h"

void Gun::fire(float xPos, float yPos, float speed) {
	float scale = 0.1; //will change to give actual scale later
	Bullet bullet(xPos, yPos, scale);
	bullet.setSpeed(0, speed);
	bulVect.push_back(bullet);
}

void Gun::main() {
	for (std::vector<Bullet>::iterator i = bulVect.begin(); i != bulVect.end(); i++) {//loop through all bullets
		i->main();
	}
}