#ifndef GUN_h
#define GUN_h

#include <vector>
#include "Bullet.h"

class Gun {
private:
	std::vector<Bullet> bulVect;
public:
	void fire(float xPos, float yPos, float speed);
	void main();
};
#endif