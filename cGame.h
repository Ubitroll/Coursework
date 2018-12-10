#ifndef _GAME_H
#define _GAME_H

/*
==================================================================================
cGame.h
==================================================================================
*/

#include <SDL.h>
#include <random>
// Game specific includes
#include "asteroidsGame.h"


using namespace std;

class cGame
{
public:
	cGame();

	void initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void cleanUp(SDL_Window* theSDLWND);
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre);
	void update();
	void update(double deltaTime);
	bool getInput(bool theLoop);
	double getElapsedSeconds();

	static cGame* getInstance();

private:

	static cGame* pInstance;
	// for framerates
	time_point< high_resolution_clock > m_lastTime;
	time_point< high_resolution_clock > m_CurrentTime;
	duration< double > deltaTime;

	// Sprites for displaying background and rocket textures
	cSprite spriteBkgd;
	cPlayer thePlayer;
	cEnemy theEnemy;
	cBullet theBullet;
	// game related variables
	vector<LPCSTR> textureName;
	vector<LPCSTR> textName;
	vector<LPCSTR> texturesToUse;
	vector<cEnemy*> theEnemies;
	vector<cBullet*> theBullets;
	vector<cSprite*> theExplosions;
	// Fonts to use
	vector<LPCSTR> fontList;
	vector<LPCSTR> fontsToUse;
	// Text for Game
	vector<LPCSTR> gameTextNames;
	vector<LPCSTR> gameTextList;
	vector<LPCSTR> highScoreTextures;
	// Game Sounds
	vector<LPCSTR> soundList;
	vector<soundType> soundTypes;
	vector<LPCSTR> soundsToUse;
	// Game objects
	// Define the elements and there position in/on the array/map
	cTexture* tempTexture;
	SDL_Rect pos;
	FPoint scale;
	SDL_Rect platformPos[7];
	int renderWidth, renderHeight;
	int theScore;
	string strScore;
	cHighScoreTable theHSTable;
	SDL_Point theAreaClicked;
	int numTableItems;
	bool gameOver;
	string theHighScoreTable;
	int theHSTableSize;
	btnTypes theBtnType;
	bool found = false;
	gameState theGameState;
	// Create vector array of button textures
	vector<LPCSTR> btnNameList;
	vector<LPCSTR> btnTexturesToUse;
	vector<SDL_Point> btnPos;
	vector <cButton> theButtons;
	cTexture* tempTextTexture;
	bool loop = true;
	int enemyNum = 0;
};

#endif
