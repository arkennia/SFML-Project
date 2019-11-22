#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "gameobject.h"

class Projectile : public GameObject
{
private:
	float velocity;
	int damage;
public:
	Projectile() {
		velocity = 0.00;
		damage = 0;
	}
	~Projectile() {

	}
	void setDmg(int newDmg) {
		damage = newDmg;
	}
	void setVel(float newVel) {
		velocity = newVel;
	}
};

#endif 