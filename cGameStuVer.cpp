/*
==================================================================================
cGame.cpp
==================================================================================
*/
#include "cGame.h"

cGame* cGame::pInstance = NULL;
static cTextureMgr* theTextureMgr = cTextureMgr::getInstance();
static cFontMgr* theFontMgr = cFontMgr::getInstance();
static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();
static cButtonMgr* theButtonMgr = cButtonMgr::getInstance();


/*
=================================================================================
Constructor
=================================================================================
*/
cGame::cGame()
{

}
/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cGame* cGame::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cGame();
	}
	return cGame::pInstance;
}


void cGame::initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	// Get width and height of render context
	SDL_GetRendererOutputSize(theRenderer, &renderWidth, &renderHeight);
	this->m_lastTime = high_resolution_clock::now();
	// Clear the buffer with a black background
	SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255);
	SDL_RenderPresent(theRenderer);

	

	theTextureMgr->setRenderer(theRenderer);
	theFontMgr->initFontLib();
	theSoundMgr->initMixer();
	theScore = 0;

	// Set platform coordinates and number of itterations into the platformPos array
	platformPos[0] = { 32,572, 13 };
	platformPos[1] = { 675, 572, 13 };
	platformPos[2] = { 32, 150, 15 };
	platformPos[3] = { 625, 150, 15 };
	platformPos[4] = { 32, 400, 6 };
	platformPos[5] = { 850, 400, 6 };
	platformPos[6] = { 319,350, 16 };

	// Store the textures
	textureName = { "Block", "Brick", "Fire", "Gromb", "Jim","Hole","HoleR","shell1", "shell2", "Thud", "JimL", "shell1R", "shell2R" };
	texturesToUse = { "Images\\Sprites\\Block.png", "Images\\Sprites\\BrickBlock.png", "Images\\Sprites\\Fireball.png", "Images\\Sprites\\Grombone.png", "Images\\Sprites\\Jim.png", "Images\\Sprites\\MonstorHole.png","Images\\Sprites\\MonstorHoleR.png", "Images\\Sprites\\ShellBoy1.png", "Images\\Sprites\\ShellBoy2.png", "Images\\Sprites\\Thud.png" , "Images\\Sprites\\JimL.png",  "Images\\Sprites\\ShellBoy1R.png", "Images\\Sprites\\ShellBoy2R.png" };
	for (int tCount = 0; tCount < (int)textureName.size(); tCount++)
	{	
		theTextureMgr->addTexture(textureName[tCount], texturesToUse[tCount]);
	}
	// Create textures for Game Dialogue (text)
	fontList = { "digital", "Arcade" };
	fontsToUse = { "Fonts/digital-7.ttf", "Fonts/Class.ttf" };
	for (int fonts = 0; fonts < (int)fontList.size(); fonts++)
	{
		theFontMgr->addFont(fontList[fonts], fontsToUse[fonts], 36);
	}
	gameTextList = { "Jim the Electrician", "Run into the turtles", "Use the arrow keys to move", "Thanks for playing", "See you again soon", "Score ", "", "High Score" };
	
	// create textures for the title and score
	theTextureMgr->addTexture("Title", theFontMgr->getFont("Arcade")->createTextTexture(theRenderer, gameTextList[0], textType::solid, { 0, 255, 0, 255 }, { 0, 0, 0, 0 }));
	theTextureMgr->addTexture("theScore", theFontMgr->getFont("Arcade")->createTextTexture(theRenderer, strScore.c_str(), textType::solid, { 0, 255, 0, 255 }, { 0, 0, 0, 0 }));

	// Load game sounds
	soundList = { "theme", "death" };
	soundTypes = { soundType::music, soundType::sfx};
	soundsToUse = { "Audio/Theme.mp3", "Audio/DeathSound.m4a"};
	for (int sounds = 0; sounds < (int)soundList.size(); sounds++)
	{
		theSoundMgr->add(soundList[sounds], soundsToUse[sounds], soundTypes[sounds]);
	}
	// Create text Textures
	gameTextNames = { "TitleTxt", "CollectTxt", "InstructTxt", "ThanksTxt", "SeeYouTxt","ScoreTxt","HSTable","HScore" };
	for (unsigned int text = 0; text < gameTextNames.size(); text++)
	{
		if (text == 0 || text == gameTextNames.size() - 1)
		{
			theTextureMgr->addTexture(gameTextNames[text], theFontMgr->getFont("Arcade")->createTextTexture(theRenderer, gameTextList[text], textType::solid, { 44, 203, 112, 255 }, { 0, 0, 0, 0 }));
		}
		else
		{
			theTextureMgr->addTexture(gameTextNames[text], theFontMgr->getFont("Arcade")->createTextTexture(theRenderer, gameTextList[text], textType::solid, { 44, 203, 112, 255 }, { 0, 0, 0, 0 }));
		}
	}
	// Store the textures
	btnNameList = { "exit_btn", "instructions_btn", "load_btn", "menu_btn", "play_btn", "save_btn", "settings_btn", "hs_btn" };
	btnTexturesToUse = { "Images/Buttons/button_exit.png", "Images/Buttons/button_instructions.png", "Images/Buttons/button_load.png", "Images/Buttons/button_menu.png", "Images/Buttons/button_play.png", "Images/Buttons/button_save.png", "Images/Buttons/button_settings.png", "Images/Buttons/button_hscore.png" };
	btnPos = { { 400, 375 }, { 400, 300 }, { 400, 300 }, { 500, 500 }, { 400, 300 }, { 740, 500 }, { 400, 300 }, { 400, 500 } };
	for (unsigned int bCount = 0; bCount < btnNameList.size(); bCount++)
	{
		theTextureMgr->addTexture(btnNameList[bCount], btnTexturesToUse[bCount]);
	}
	for (unsigned int bCount = 0; bCount < btnNameList.size(); bCount++)
	{
		cButton * newBtn = new cButton();
		newBtn->setTexture(theTextureMgr->getTexture(btnNameList[bCount]));
		newBtn->setSpritePos(btnPos[bCount]);
		newBtn->setSpriteDimensions(theTextureMgr->getTexture(btnNameList[bCount])->getTWidth(), theTextureMgr->getTexture(btnNameList[bCount])->getTHeight());
		theButtonMgr->add(btnNameList[bCount], newBtn);
	}
	theGameState = gameState::menu;
	theBtnType = btnTypes::exit;

	theSoundMgr->getSnd("theme")->play(-1);

	
	
	// Code to spawn single itteration of an enemy for testing purposes
	/*theEnemy.setSpritePos({ 132, 150 });
	theEnemy.setTexture(theTextureMgr->getTexture("shell1"));
	theEnemy.setSpriteDimensions(theTextureMgr->getTexture("shell1")->getTWidth(), theTextureMgr->getTexture("shell1")->getTHeight());
	theEnemy.setEnemyVelocity(100);
	theEnemy.setSpriteTranslation({ 50,50 });*/
	


	// High score stuff
	numTableItems = 0;
	theHSTable.loadFromFile("Data/HighScore.dat");

	theHighScoreTable = gameTextList[6];

	theHSTableSize = theHSTable.getTableSize();
	highScoreTextures = { "score1","score2","score3","score4","score5","score6","score7","score8","score9","score10" };

	for (int item = 0; item < theHSTableSize; item++)
	{
		string entry = "";
		entry += theHSTable.getItem(item).Name + " " + to_string(theHSTable.getItem(item).score);
		theTextureMgr->addTexture(highScoreTextures[item], theFontMgr->getFont("Arcade")->createTextTexture(theRenderer, entry.c_str(), textType::solid, { 44, 203, 112, 255 }, { 0, 0, 0, 0 }));
	}

	// Spawn Player and set everything up.
	thePlayer.setSpritePos({ 32, 615 });
	thePlayer.setTexture(theTextureMgr->getTexture("Jim"));
	thePlayer.setSpriteDimensions(theTextureMgr->getTexture("Jim")->getTWidth(), theTextureMgr->getTexture("Jim")->getTHeight());
	thePlayer.setPlayerVelocity(100);
	thePlayer.setSpriteTranslation({ 50,50 });

	// sets gameover to false
	gameOver = false;
}

void cGame::run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	//bool loop = true;

	while (loop)
	{
		//We get the time that passed since the last frame
		double elapsedTime = this->getElapsedSeconds();

		loop = this->getInput(loop);
		this->update(elapsedTime);
		this->render(theSDLWND, theRenderer);
	}
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	SDL_RenderClear(theRenderer);
	switch (theGameState)
	{
	case gameState::menu:
	{
		// Render the Title
		tempTextTexture = theTextureMgr->getTexture("TitleTxt");
		pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		scale = { 1, 1 };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		tempTextTexture = theTextureMgr->getTexture("CollectTxt");
		pos = { 50, 100, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		tempTextTexture = theTextureMgr->getTexture("InstructTxt");
		pos = { 50, 175, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		// Render Button
		theButtonMgr->getBtn("play_btn")->setSpritePos({ 400, 375 });
		theButtonMgr->getBtn("play_btn")->render(theRenderer, &theButtonMgr->getBtn("play_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("play_btn")->getSpritePos(), theButtonMgr->getBtn("play_btn")->getSpriteScale());
		theButtonMgr->getBtn("hs_btn")->setSpritePos({ 400, 425 });
		theButtonMgr->getBtn("hs_btn")->render(theRenderer, &theButtonMgr->getBtn("hs_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("hs_btn")->getSpritePos(), theButtonMgr->getBtn("hs_btn")->getSpriteScale());
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 400, 475 });
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale());
	}
	break;
	case gameState::playing:
	{
		// Renders the line of bricks at the bottom of the screen through an array
		tempTexture = theTextureMgr->getTexture("Brick");
		pos = { 32, 700, tempTexture->getTextureRect().w, tempTexture->getTextureRect().h };
		scale = { 1, 1 };
		for (int draw = 0; draw < 16; draw++)
		{
			tempTexture->renderTexture(theRenderer, tempTexture->getTexture(), &tempTexture->getTextureRect(), &pos, scale);
			pos.x = 32 + (draw * tempTexture->getTextureRect().w);
		}

		// Uses the pre set platform positions to render different sized platforms across the screen.
		tempTexture = theTextureMgr->getTexture("Block");
		for (int platforms = 0; platforms < 7; platforms++)
		{
			pos = { platformPos[platforms].x, platformPos[platforms].y, tempTexture->getTextureRect().w, tempTexture->getTextureRect().h };
			for (int draw = 0; draw < platformPos[platforms].w; draw++)
			{
				tempTexture->renderTexture(theRenderer, tempTexture->getTexture(), &tempTexture->getTextureRect(), &pos, scale);
				pos.x = pos.x + tempTexture->getTextureRect().w;
			}
		}

		// Renders the two monster spawn points at the top of the screen.
		tempTexture = theTextureMgr->getTexture("HoleR");
		pos = { 32, 86, tempTexture->getTextureRect().w, tempTexture->getTextureRect().h };
		scale = { 1, 1 };
		tempTexture->renderTexture(theRenderer, tempTexture->getTexture(), &tempTexture->getTextureRect(), &pos, scale);
		tempTexture = theTextureMgr->getTexture("Hole");
		pos = { 904, 86, tempTexture->getTextureRect().w, tempTexture->getTextureRect().h };
		tempTexture->renderTexture(theRenderer, tempTexture->getTexture(), &tempTexture->getTextureRect(), &pos, scale);

		// Renders the THUD block 
		tempTexture = theTextureMgr->getTexture("Thud");
		pos = { 500, 500, tempTexture->getTextureRect().w, tempTexture->getTextureRect().h };
		scale = { 1, 1 };
		tempTexture->renderTexture(theRenderer, tempTexture->getTexture(), &tempTexture->getTextureRect(), &pos, scale);

		// Render each enemy in the vector array
		for (int draw = 0; draw < (int)theEnemies.size(); draw++)
		{
			theEnemies[draw]->render(theRenderer, &theEnemies[draw]->getSpriteDimensions(), &theEnemies[draw]->getSpritePos(), theEnemies[draw]->getSpriteRotAngle(), &theEnemies[draw]->getSpriteCentre(), theEnemies[draw]->getSpriteScale());
		}

		// Render the Title
		cTexture* tempTextTexture = theTextureMgr->getTexture("Title");
		SDL_Rect pos = { 32, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		FPoint scale = { 1, 1 };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);

		// Render score value and only updates score when the number of enemies is equal to 0
		if (theScore == 0)
		{

			theScore = 0;
			theTextureMgr->deleteTexture("theScore");
			strScore = gameTextList[5];
			strScore += to_string(theScore).c_str();
			theTextureMgr->addTexture("theScore", theFontMgr->getFont("Arcade")->createTextTexture(theRenderer, strScore.c_str(), textType::solid, { 0, 255, 0, 255 }, { 0, 0, 0, 0 }));

		}
		if (enemyNum == 0)
		{

			theScore = theScore + 100;
			theTextureMgr->deleteTexture("theScore");
			strScore = gameTextList[5];
			strScore += to_string(theScore).c_str();
			theTextureMgr->addTexture("theScore", theFontMgr->getFont("Arcade")->createTextTexture(theRenderer, strScore.c_str(), textType::solid, { 0, 255, 0, 255 }, { 0, 0, 0, 0 }));
			
		}
		cTexture* tempTextTexture2 = theTextureMgr->getTexture("theScore");
		SDL_Rect pos2 = { 700, 10, tempTextTexture2->getTextureRect().w, tempTextTexture2->getTextureRect().h };
		FPoint scale2 = { 1, 1 };
		tempTextTexture2->renderTexture(theRenderer, tempTextTexture2->getTexture(), &tempTextTexture2->getTextureRect(), &pos2, scale2);
		thePlayer.render(theRenderer, &thePlayer.getSpriteDimensions(), &thePlayer.getSpritePos(), thePlayer.getSpriteRotAngle(), &thePlayer.getSpriteCentre(), thePlayer.getSpriteScale());
	}
	break;
	case gameState::end:
	{
		// Render's buttons on end screen
		theButtonMgr->getBtn("play_btn")->setSpritePos({ 250, 375 });
		theButtonMgr->getBtn("play_btn")->render(theRenderer, &theButtonMgr->getBtn("play_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("play_btn")->getSpritePos(), theButtonMgr->getBtn("play_btn")->getSpriteScale());
		theButtonMgr->getBtn("menu_btn")->setSpritePos({ 250, 425 });
		theButtonMgr->getBtn("menu_btn")->render(theRenderer, &theButtonMgr->getBtn("menu_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("menu_btn")->getSpritePos(), theButtonMgr->getBtn("menu_btn")->getSpriteScale());
	}
	break;
	case gameState::highscore:
	{
		
		// Render the Title
		tempTextTexture = theTextureMgr->getTexture("HScore");
		pos = { 220, 125, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		scale = { 1, 1 };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		pos = { 220, 200, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };

		// rebder high score
		for (int item = 0; item < theHSTableSize; item++)
		{
			tempTextTexture = theTextureMgr->getTexture(highScoreTextures[item]);
			tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
			pos = { 220, 200 + (50 * item), tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		}

		// Render Button
		theButtonMgr->getBtn("play_btn")->setSpritePos({ 900, 375 });
		theButtonMgr->getBtn("play_btn")->render(theRenderer, &theButtonMgr->getBtn("play_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("play_btn")->getSpritePos(), theButtonMgr->getBtn("play_btn")->getSpriteScale());
		theButtonMgr->getBtn("menu_btn")->setSpritePos({ 900, 425 });
		theButtonMgr->getBtn("menu_btn")->render(theRenderer, &theButtonMgr->getBtn("menu_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("menu_btn")->getSpritePos(), theButtonMgr->getBtn("menu_btn")->getSpriteScale());
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 900, 475 });
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale());
	}
	break;
	case gameState::quit:
	{
		// Sets the game to quit and saves the score to the highscore file
		loop = false;
		theHSTable.addItem("Stephen", theScore);
		theHSTable.saveToFile("Data/HighScore.dat");
	}
	break;
	default:
		break;
	}
	SDL_RenderPresent(theRenderer);
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre)
{
	SDL_RenderPresent(theRenderer);
}

void cGame::update()
{

}

void cGame::update(double deltaTime)
{
	// If on the menu or highscore exit button will quit
	if (theGameState == gameState::menu || theGameState == gameState::highscore)
	{
		
		theGameState = theButtonMgr->getBtn("exit_btn")->update(theGameState, gameState::quit, theAreaClicked);
	}
	// If in highscore the play and menu buttons wil take you to the game and menu respectivly
	if (theGameState == gameState::highscore)
	{
		
		theGameState = theButtonMgr->getBtn("play_btn")->update(theGameState, gameState::playing, theAreaClicked);
		theGameState = theButtonMgr->getBtn("menu_btn")->update(theGameState, gameState::menu, theAreaClicked);
	}
	// In the meny the play and highscore button will take you to the game and highcore screen respectivly
	if (theGameState == gameState::menu)
	{
		theGameState = theButtonMgr->getBtn("play_btn")->update(theGameState, gameState::playing, theAreaClicked);
		theGameState = theButtonMgr->getBtn("hs_btn")->update(theGameState, gameState::highscore, theAreaClicked);
		// If the game has been plyed through reset the gamme variabes
		if (theGameState == gameState::playing && gameOver == false)
		{
			theScore = 0;
			enemyNum = 0;
			thePlayer.setSpritePos({ 32, 615 });
			gameOver = false;

		}
		// set the area clicked to 0,0 to avoid a button being clicked when not wanted
		theAreaClicked = { 0,0 };
	}

	// if gamestate is end play and menu button will take you to their respective screens.
	if (theGameState == gameState::end)
	{
		theButtonMgr->getBtn("play_btn")->setClicked(false);
		theGameState = theButtonMgr->getBtn("play_btn")->update(theGameState, gameState::playing, theAreaClicked);
		theGameState = theButtonMgr->getBtn("menu_btn")->update(theGameState, gameState::menu, theAreaClicked);

		// reset game variables if play is pressed
		if (theGameState == gameState::playing && gameOver == true)
		{
			gameOver = false;
			thePlayer.setSpritePos({ 32, 615 });
			enemyNum = 0;
			theScore = 0;
		}
		// set the area clicked to 0,0 to avoid a button being clicked when not wanted
		theAreaClicked = { 0,0 };
	}
	// if game state is playing 
	if (theGameState == gameState::playing)
	{
		theButtonMgr->getBtn("play_btn")->setClicked(false);
		theAreaClicked = { 0,0 };
		/* Let the computer pick a random number */
		random_device rd;    // non-deterministic engine 
		mt19937 gen{ rd() }; // deterministic engine. For most common uses, std::mersenne_twister_engine, fast and high-quality.
		uniform_int_distribution<> EnemyDis{ 1, 5 };
		uniform_int_distribution<> EnemyTextDis{ 7, 8 };
		uniform_int_distribution<> EnemyTextDis2{ 11, 12 };
		uniform_int_distribution<> EnemyVelocity{ 200, 300 };

		// Spawns new wave of enemies only if the score hasn't reached the win point and there are no enemies on the screen
		// If score hasn't reach win condition
		if (theScore < 1000) 
		{
			// If no enemies on screen
			if (enemyNum == 0)
			{
				// Spawn enemies that are traveling  to the right
				for (int enem = 0; enem < 3; enem++)
				{
					theEnemies.push_back(new cEnemy);
					theEnemies[enem]->setSpritePos({ 904, 68 });
					theEnemies[enem]->setSpriteTranslation({ 100, -50 });
					int randEnemy = EnemyTextDis(gen);
					theEnemies[enem]->setTexture(theTextureMgr->getTexture(textureName[randEnemy]));
					theEnemies[enem]->setSpriteDimensions(theTextureMgr->getTexture(textureName[randEnemy])->getTWidth(), theTextureMgr->getTexture(textureName[randEnemy])->getTHeight());
					theEnemies[enem]->setEnemyVelocity(EnemyVelocity(gen));
					theEnemies[enem]->setActive(true);
					enemyNum++;
				}
				// Spawn enemies that are traveling to the left
				for (int enem = theEnemies.size(); enem < 6; enem++)
				{
					theEnemies.push_back(new cEnemy);
					theEnemies[enem]->setSpritePos({ 32, 68 });
					theEnemies[enem]->setSpriteTranslation({ 100, -50 });
					int randEnemy = EnemyTextDis2(gen);
					theEnemies[enem]->setTexture(theTextureMgr->getTexture(textureName[randEnemy]));
					theEnemies[enem]->setSpriteDimensions(theTextureMgr->getTexture(textureName[randEnemy])->getTWidth(), theTextureMgr->getTexture(textureName[randEnemy])->getTHeight());
					theEnemies[enem]->setEnemyVelocity(-EnemyVelocity(gen));
					theEnemies[enem]->setActive(true);
					enemyNum++;
				}
			}
		}
		// Enemy iterator
		for (vector<cEnemy*>::iterator enemyIterator = theEnemies.begin(); enemyIterator != theEnemies.end(); ++enemyIterator)
		{
			if ((*enemyIterator)->collidedWith(&(*enemyIterator)->getBoundingRect(), &thePlayer.getBoundingRect()))
			{
				// if a collision set the bullet and asteroid to false
				(*enemyIterator)->setActive(false);

				theSoundMgr->getSnd("death")->play(0);

				// Reduce the number of enemies on the screen
				enemyNum--;
			}
		}
		// Update the visibility and position of each enemy
		vector<cEnemy*>::iterator enemyIterator = theEnemies.begin();
		while (enemyIterator != theEnemies.end())
		{
			if ((*enemyIterator)->isActive() == false)
			{
				enemyIterator = theEnemies.erase(enemyIterator);
			}
			else
			{
				(*enemyIterator)->update(deltaTime, platformPos);
				++enemyIterator;
			}
		}
		// Update the player position
		thePlayer.update(deltaTime);
		// For use of single enemy iteration
		//theEnemy.update(deltaTime, platformPos);
		
		// Chcecks to see if player has landed on a platform
		int p = 0;
		while (!found && p < 7)
		{
			if (platformPos[p].x <= thePlayer.getSpritePos().x && platformPos[p].x + 25 * platformPos[p].w >= thePlayer.getSpritePos().x)
			{
				if (platformPos[p].y == thePlayer.getSpritePos().y + 84)
				{
					// Stops the player from falling as they have landed on a platform
					thePlayer.setPlayerFalling(false);
					found = true;
				}
				else
				{
					// The player must be falling
					thePlayer.setPlayerFalling(true);
				}
			}
			p++;
		}
		// If the player lands on the bottom bricks stop them from falling
		if (thePlayer.getSpritePos().y == 616)
		{
			thePlayer.setPlayerFalling(false);
		}
		if (found == true)
		{
			found = false;
		}

		// Create SDL points to teleport the player to for the far right and far left of the screen
		SDL_Point farRight = { WINDOW_WIDTH - 90, thePlayer.getSpritePos().y };
		SDL_Point farLeft = { 32, thePlayer.getSpritePos().y };
		
		// IF the player walks off the left side of the screen
		if (thePlayer.getSpritePos().x < 32)
		{
			// Teleport them to the right of the screen
			thePlayer.setSpritePos(farRight);
		}
		// Else if the player walks off the right of the screen
		else if (thePlayer.getSpritePos().x > (WINDOW_WIDTH - 90))
		{
			// Teleport the player to the left of the screen
			thePlayer.setSpritePos(farLeft);
		}
		// If the score reaches 1000 player wins and gameover is called
		if (theScore == 1000)
		{
			theGameState = gameState::end;
			gameOver = true;
		}
	}
	// If loop is false quit game
	if (loop == false)
	{
		//theGameState == gameState::quit;
		SDL_Quit();
	}
}

bool cGame::getInput(bool theLoop)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			theLoop = false;
		}

		switch (event.type)
		{
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button)
				{
					case SDL_BUTTON_LEFT:
					{
						// If in a gamestate that you can use the mouse allow left click to inout an area clicked
						if (theGameState == gameState::menu || theGameState == gameState::highscore || theGameState == gameState::end) 
						{
							theAreaClicked = { event.motion.x, event.motion.y };
						}
					}
					break;
					case SDL_BUTTON_RIGHT:
						break;
					default:
						break;
					}
					break;
				case SDL_MOUSEBUTTONUP:
					switch (event.button.button)
					{
					case SDL_BUTTON_LEFT:
					{
					}
					break;
					case SDL_BUTTON_RIGHT:
						break;
					default:
						break;
					}
					break;
				case SDL_MOUSEMOTION:
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					theLoop = false;
					break;
				case SDLK_DOWN:
				{
					
				}
				break;

				case SDLK_UP:
				{
					// If in the gamestate playing 
					if (theGameState == gameState::playing) 
					{
						// When space is pressed make the player jump if they aren't jumping already
						if (thePlayer.getPlayerJumping() == false)
						{
							thePlayer.setPlayerJumping(true);
						}
					}
				}
				break;
				case SDLK_RIGHT:
				{
					// If in the gamestate playing 
					if (theGameState == gameState::playing)
					{
						// make player walk
						thePlayer.setPlayerWalking(true);
						thePlayer.setTexture(theTextureMgr->getTexture("Jim"));
						thePlayer.setSpriteDimensions(theTextureMgr->getTexture("Jim")->getTWidth(), theTextureMgr->getTexture("Jim")->getTHeight());
						thePlayer.setPlayerMove(1);
					}
				}
				break;
				
				case SDLK_LEFT:
				{
					// If in the gamestate playing 
					if (theGameState == gameState::playing)
					{
						// make player walk
						thePlayer.setPlayerWalking(true);
						thePlayer.setTexture(theTextureMgr->getTexture("JimL"));
						thePlayer.setSpriteDimensions(theTextureMgr->getTexture("JimL")->getTWidth(), theTextureMgr->getTexture("JimL")->getTHeight());
						thePlayer.setPlayerMove(-1);
					}
				}
				break;
				case SDLK_SPACE:
				{
					
				}
				
				break;
				default:
					break;
				}

			default:
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
				// When the right key is lifted up stop movement
				case SDLK_RIGHT:
				{
					if (theGameState == gameState::playing) 
					{
						thePlayer.setPlayerWalking(false);
						thePlayer.setTexture(theTextureMgr->getTexture("Jim"));
						thePlayer.setSpriteDimensions(theTextureMgr->getTexture("Jim")->getTWidth(), theTextureMgr->getTexture("Jim")->getTHeight());
						thePlayer.setPlayerMove(0);
					}
				}
				break;
				// When the left key is lifted up stop movement
				case SDLK_LEFT:
				{
					if (theGameState == gameState::playing)
					{
						thePlayer.setPlayerWalking(false);
						thePlayer.setTexture(theTextureMgr->getTexture("JimL"));
						thePlayer.setSpriteDimensions(theTextureMgr->getTexture("JimL")->getTWidth(), theTextureMgr->getTexture("JimL")->getTHeight());
						thePlayer.setPlayerMove(0);
					}
				}
				break;
				// When the space key is lifted stop jumping
				case SDLK_SPACE:
				{
					thePlayer.setPlayerJumping(false);
				}
				break;
				}
		}

	}
	return theLoop;
}

double cGame::getElapsedSeconds()
{
	this->m_CurrentTime = high_resolution_clock::now();
	this->deltaTime = (this->m_CurrentTime - this->m_lastTime);
	this->m_lastTime = this->m_CurrentTime;
	return deltaTime.count();
}

void cGame::cleanUp(SDL_Window* theSDLWND)
{
	// Delete our OpengL context
	SDL_GL_DeleteContext(theSDLWND);

	// Destroy the window
	SDL_DestroyWindow(theSDLWND);

	//Quit FONT system
	TTF_Quit();

	// Quit IMG system
	IMG_Quit();

	// Shutdown SDL 2
	SDL_Quit();
}

