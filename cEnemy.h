/*
=================
cAsteroid.h
- Header file for class definition - SPECIFICATION
- Header file for the Rocket class which is a child of cSprite class
=================
*/
#ifndef _CENEMY_H
#define _CENEMY_H
#include "cSprite.h"

class cEnemy : public cSprite
{
private:
	int enemyVelocity;
	bool found = false;
	bool fall = false;

public:
	cEnemy();
	void update(double deltaTime, SDL_Rect platformPos[7]);		// Rocket update method
	void setEnemyVelocity(int enemyVel);   // Sets the velocity for the asteroid
	int getEnemyVelocity();				 // Gets the asteroid velocity
	void setEnemyFalling(bool falling);	// Sets if the enemy is falling
	bool getEnemyFalling();				// Gets if the enemy is falling
};
#endif