/*
=================
cPlayer.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cPlayer.h"

/*
=================================================================
Defualt Constructor
=================================================================
*/
cPlayer::cPlayer() : cSprite()
{
	this->playerVelocity = 0;
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cPlayer::update(double deltaTime)
{

	auto rads = PI / 180.0f * (this->getSpriteRotAngle() - 90.0f);

	FPoint direction = { 0.0f, 0.0f };
	direction.X = (float)(cos(rads));
	direction.Y = (float)(sin(rads));

	SDL_Rect currentSpritePos = this->getSpritePos();

	// If walking move in desired direvtion
	if (walk == true)
	{
		currentSpritePos.x += (int)(this->playerVelocity * 1 * this->move * 0.05);
	}

	// If the player is jumping
	if (jump == true)
	{
		for (int fall = 1; fall > 0; fall = fall - 0.1)
		{
			currentSpritePos.y -= (int)(this->playerVelocity * 1 * 1);
			// If walking is also true allow movement while falling and jumping
			if (walk == true)
			{
				currentSpritePos.x += (int)(this->playerVelocity * 1 * this->move * 0.01);
			}
		}
		jump = false;
	}

	// Origional Psuedocode for gravity system
	// if not touching collider AND not jumping
	// {
	//	currentSpritePos.y += (int)(this->rocketVelocity * 1 * 0.02);
	// }
	if (fall == true && jump == false)
	{
		currentSpritePos.y += (int)(this->playerVelocity * 1 * 0.01);
	}
	
	// Set sprite pos and a bounding rect
	this->setSpritePos({ currentSpritePos.x , currentSpritePos.y  });
	this->setBoundingRect(this->getSpritePos());

}
/*
=================================================================
Sets the velocity for the rocket
=================================================================
*/
void cPlayer::setPlayerVelocity(int rocketVel)
{
	playerVelocity = rocketVel;
}
/*
=================================================================
Gets the rocket velocity
=================================================================
*/
int cPlayer::getPlayerVelocity()
{
	return playerVelocity;
}
/*
=================================================================
Sets the move value for the player
=================================================================
*/
void cPlayer::setPlayerMove(int playerMove)
{
	move = playerMove;
}
/*
=================================================================
Sets the player move value
=================================================================
*/
int cPlayer::getPlayerMove()
{
	return move;
}
/*
=================================================================
sets if the player is jumping
=================================================================
*/
void cPlayer::setPlayerJumping(bool jumping) 
{
	jump = jumping;
}
/*
================================================================ =
Gets if the player is jumping
================================================================ =
*/
bool cPlayer::getPlayerJumping()
{
	return jump;
}
/*
================================================================ =
sets the player to walking 
================================================================ =
*/
void cPlayer::setPlayerWalking(bool walking)
{
	walk = walking;
}
/*
================================================================ =
Gets if player walking
================================================================ =
*/
bool cPlayer::getPlayerWalking()
{
	return walk;
}
/*
================================================================ =
set player falling
================================================================ =
*/
void cPlayer::setPlayerFalling(bool falling)
{
	fall = falling;
}
/*
================================================================ =
Gets if player falling
================================================================ =
*/
bool cPlayer::getPlayerFalling()
{
	return fall;
}