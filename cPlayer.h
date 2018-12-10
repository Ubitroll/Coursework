/*
=================
cRocket.h
- Header file for class definition - SPECIFICATION
- Header file for the Rocket class which is a child of cSprite class
=================
*/
#ifndef _CPLAYER_H
#define _CPLAYER_H
#include "cSprite.h"

class cPlayer : public cSprite
{
private:
	int playerVelocity;
	int move;
	int moveUp;
	bool jump = false;
	bool walk = false;
	bool fall = true;

public:
	cPlayer();
	void update(double deltaTime);			// Rocket update method
	void setPlayerVelocity(int playerVel);  // Sets the rocket velocity
	int getPlayerVelocity();				// Gets the rocket velocity
	void setPlayerMove(int playerMove);		// Sets the rocket move Value
	int getPlayerMove();					// Gets the rocket move value
	void setPlayerJumping(bool jumping);	// Sets if player is jumping
	bool getPlayerJumping();				// Gets if player is jumping
	void setPlayerWalking(bool walking);	// Sets if the player is walking
	bool getPlayerWalking();				// Gets if the player is walking
	void setPlayerFalling(bool falling);	// Sets if the player is falling
	bool getPlayerFalling();				// Gets if the player is falling
}; 
#endif