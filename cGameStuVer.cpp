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
	
	
	theTextureMgr->addTexture("Title", theFontMgr->getFont("Arcade")->createTextTexture(theRenderer, gameTextList[0], textType::solid, { 0, 255, 0, 255 }, { 0, 0, 0, 0 }));
	theTextureMgr->addTexture("theScore", theFontMgr->getFont("Arcade")->createTextTexture(theRenderer, strScore.c_str(), textType::solid, { 0, 255, 0, 255 }, { 0, 0, 0, 0 }));

	// Load game sounds
	soundList = { "theme", "death" };
	soundTypes = { soundType::music, soundType::sfx};
	soundsToUse = { "Audio/Theme.mp3g", "Audio/DeathSound.m4a"};
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

	
	

	/*theEnemy.setSpritePos({ 132, 150 });
	theEnemy.setTexture(theTextureMgr->getTexture("shell1"));
	theEnemy.setSpriteDimensions(theTextureMgr->getTexture("shell1")->getTWidth(), theTextureMgr->getTexture("shell1")->getTHeight());
	theEnemy.setEnemyVelocity(100);
	theEnemy.setSpriteTranslation({ 50,50 });*/
	// Create vector array of textures



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
	thePlayer.setSpritePos({ 32, 615 });
	thePlayer.setTexture(theTextureMgr->getTexture("Jim"));
	thePlayer.setSpriteDimensions(theTextureMgr->getTexture("Jim")->getTWidth(), theTextureMgr->getTexture("Jim")->getTHeight());
	thePlayer.setPlayerVelocity(100);
	thePlayer.setSpriteTranslation({ 50,50 });
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
		/*spriteBkgd.setTexture(theTextureMgr->getTexture("OpeningScreen"));
		spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("OpeningScreen")->getTWidth(), theTextureMgr->getTexture("OpeningScreen")->getTHeight());
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());*/
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
		//spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
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

		// Render each bullet in the vector array
		/*for (int draw = 0; draw < (int)theBullets.size(); draw++)
		{
			theBullets[draw]->render(theRenderer, &theBullets[draw]->getSpriteDimensions(), &theBullets[draw]->getSpritePos(), theBullets[draw]->getSpriteRotAngle(), &theBullets[draw]->getSpriteCentre(), theBullets[draw]->getSpriteScale());
		}*/
		// Render each explosion in the vector array
		/*for (int draw = 0; draw < (int)theExplosions.size(); draw++)
		{
			theExplosions[draw]->render(theRenderer, &theExplosions[draw]->getSourceRect(), &theExplosions[draw]->getSpritePos(), theExplosions[draw]->getSpriteScale());
		}*/
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

		// Render updated score value
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
	if (theGameState == gameState::menu || theGameState == gameState::highscore)
	{
		
		theGameState = theButtonMgr->getBtn("exit_btn")->update(theGameState, gameState::quit, theAreaClicked);
	}
	
	if (theGameState == gameState::highscore)
	{
		
		theGameState = theButtonMgr->getBtn("play_btn")->update(theGameState, gameState::playing, theAreaClicked);
		theGameState = theButtonMgr->getBtn("menu_btn")->update(theGameState, gameState::menu, theAreaClicked);
	}

	if (theGameState == gameState::menu)
	{
		theGameState = theButtonMgr->getBtn("play_btn")->update(theGameState, gameState::playing, theAreaClicked);
		theGameState = theButtonMgr->getBtn("hs_btn")->update(theGameState, gameState::highscore, theAreaClicked);
		if (theGameState == gameState::playing && gameOver == false)
		{
			theScore = 0;
			enemyNum = 0;
			thePlayer.setSpritePos({ 32, 615 });
			gameOver = false;

		}
		
		theAreaClicked = { 0,0 };
	}

	//theGameState = theButtonMgr->getBtn("menu_btn")->update(theGameState, gameState::menu, theAreaClicked);

	if (theGameState == gameState::end)
	{
		theButtonMgr->getBtn("play_btn")->setClicked(false);
		theGameState = theButtonMgr->getBtn("play_btn")->update(theGameState, gameState::playing, theAreaClicked);
		theGameState = theButtonMgr->getBtn("menu_btn")->update(theGameState, gameState::menu, theAreaClicked);

		if (theGameState == gameState::playing && gameOver == true)
		{
			gameOver = false;
			thePlayer.setSpritePos({ 32, 615 });
			enemyNum = 0;
			theScore = 0;
		}
		theAreaClicked = { 0,0 };
	}
	
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

		if (theScore < 1000) {
			if (enemyNum == 0)
			{

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
		for (vector<cEnemy*>::iterator enemyIterator = theEnemies.begin(); enemyIterator != theEnemies.end(); ++enemyIterator)
		{
			if ((*enemyIterator)->collidedWith(&(*enemyIterator)->getBoundingRect(), &thePlayer.getBoundingRect()))
			{
				// if a collision set the bullet and asteroid to false
				(*enemyIterator)->setActive(false);

				theSoundMgr->getSnd("death")->play(0);

				// Lab 7 code goes here
					
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
		// Update the Rockets position
		thePlayer.update(deltaTime);
		//theEnemy.update(deltaTime, platformPos);
		int p = 0;
		while (!found && p < 7)
		{
			if (platformPos[p].x <= thePlayer.getSpritePos().x && platformPos[p].x + 25 * platformPos[p].w >= thePlayer.getSpritePos().x)
			{
				if (platformPos[p].y == thePlayer.getSpritePos().y + 84)
				{
					thePlayer.setPlayerFalling(false);
					found = true;
				}
				else
				{
					thePlayer.setPlayerFalling(true);
				}
			}
			p++;
		}
		if (thePlayer.getSpritePos().y == 616)
		{
			thePlayer.setPlayerFalling(false);
		}
		if (found == true)
		{
			found = false;
		}
		SDL_Point farRight = { WINDOW_WIDTH - 90, thePlayer.getSpritePos().y };

		SDL_Point farLeft = { 32, thePlayer.getSpritePos().y };


		if (thePlayer.getSpritePos().x < 32)
		{
			thePlayer.setSpritePos(farRight);
		}
		else if (thePlayer.getSpritePos().x > (WINDOW_WIDTH - 90))
		{
			thePlayer.setSpritePos(farLeft);
		}

		if (theScore == 1000)
		{
			theGameState = gameState::end;
			gameOver = true;
		}


		
	}
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
					if (theGameState == gameState::playing) 
					{
						// When space is pressed make the player jump
						if (thePlayer.getPlayerJumping() == false)
						{
							thePlayer.setPlayerJumping(true);
						}
					}
				}
				break;
				case SDLK_RIGHT:
				{
					if (theGameState == gameState::playing)
					{
						thePlayer.setPlayerWalking(true);
						thePlayer.setTexture(theTextureMgr->getTexture("Jim"));
						thePlayer.setSpriteDimensions(theTextureMgr->getTexture("Jim")->getTWidth(), theTextureMgr->getTexture("Jim")->getTHeight());
						thePlayer.setPlayerMove(1);
						/*if (thePlayer.getSpriteRotAngle() == 5)
						{
							thePlayer.setSpriteRotAngle(thePlayer.getSpriteRotAngle() - 10);
						}
						else if (thePlayer.getSpriteRotAngle() == -5)
						{
							thePlayer.setSpriteRotAngle(thePlayer.getSpriteRotAngle() + 10);
						}*/
					}
				}
				break;
				
				case SDLK_LEFT:
				{
					if (theGameState == gameState::playing)
					{
						thePlayer.setPlayerWalking(true);
						thePlayer.setTexture(theTextureMgr->getTexture("JimL"));
						thePlayer.setSpriteDimensions(theTextureMgr->getTexture("JimL")->getTWidth(), theTextureMgr->getTexture("JimL")->getTHeight());
						thePlayer.setPlayerMove(-1);
						/*if (thePlayer.getSpriteRotAngle() == 5)
						{
							thePlayer.setSpriteRotAngle(thePlayer.getSpriteRotAngle() - 10);
						}
						else if (thePlayer.getSpriteRotAngle() == -5)
						{
							thePlayer.setSpriteRotAngle(thePlayer.getSpriteRotAngle() + 10);
						}*/
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

