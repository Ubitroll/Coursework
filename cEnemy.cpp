/*
=================
cEnemy.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cEnemy.h"

/*
=================================================================
Defualt Constructor
=================================================================
*/
cEnemy::cEnemy() : cSprite()
{
	this->enemyVelocity = 100;
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cEnemy::update(double deltaTime, SDL_Rect platformPos[7])
{
	// Checks if the enemy lands on a platoform
	int p = 0;
	while (!found && p < 7)
	{
		if (platformPos[p].x <= this->getSpritePos().x && platformPos[p].x + 25 * platformPos[p].w >= this->getSpritePos().x)
		{
			if (platformPos[p].y == this->getSpritePos().y + 20)
			{
				// stops falling
				this->setEnemyFalling(false);
				found = true;
			}
			else
			{
				// else must be falling
				this->setEnemyFalling(true);
			}
		}
		p++;
	}
	if (found == true)
	{
		found = false;
	}
	
	// Sets up SDL teleportation points
	SDL_Point farRightEnemy = { WINDOW_WIDTH - 90, this->getSpritePos().y };
	SDL_Point farLeftEnemy = { 32, this->getSpritePos().y };

	// If walks off screen left move to right side of screen
	if (this->getSpritePos().x < 32)
	{
		this->setSpritePos(farRightEnemy);
	}
	// Else if player walks off screen right move to left side of the screen
	else if (this->getSpritePos().x > (WINDOW_WIDTH - 90))
	{
		this->setSpritePos(farLeftEnemy);
	}
	// Makes the enemey constantly walk
	this->setSpritePos({  this->getSpritePos().x + (int)(this->enemyVelocity * -1 * 0.03),this->getSpritePos().y });
	// If enemy lands on bottom bricks stop falling
	if (this->getSpritePos().y == 680)
	{
		this->setEnemyFalling(false);
	}
	// Create bounding rect for enemy
	this->setBoundingRect(this->getSpritePos());
	// If falling move sprite down
	if (fall == true )
	{
		this->setSpritePos({ this->getSpritePos().x, this->getSpritePos().y + (int)(100 * 1 * 0.01) });
	}
	
}
/*
=================================================================
  Sets the velocity for the enemy
=================================================================
*/
void cEnemy::setEnemyVelocity(int enemyVel)
{
	enemyVelocity = enemyVel;
}
/*
=================================================================
  Gets the enemy velocity
=================================================================
*/
int cEnemy::getEnemyVelocity()
{
	return enemyVelocity;
}
/*
=================================================================
  Sets if the enemy is falling
=================================================================
*/
void cEnemy::setEnemyFalling(bool falling)
{
	fall = falling;
}
/*
================================================================ =
Gets if enemy falling
================================================================ =
*/
bool cEnemy::getEnemyFalling()
{
	return fall;
}