#include "TurnHandler.h"
#include "EntityManager.h"
#include "Game.h"
#include "Player.h"
#include <iostream>
#include <sstream>

#include <irrKlang.h>
using namespace irrklang;

ISoundEngine* engine3 = createIrrKlangDevice();				// start the sound engine with default parameters

using namespace irr;
using namespace irr::core;
using namespace irr::gui;
int x = 0;
int y = 1;
int playersLeft = 8;

void TurnHandler::initialise() { }

void TurnHandler::loadContent() { }

void TurnHandler::handleMessage(const Message& message) { }

void TurnHandler::update(float frameTime)
{
	//This gets the players by searching through the list of entities till it find the one called player1
	//and sets it as the variable p1. from this you can access all the methods and stuff from the player
	Player* p1 = (Player*)EntityManager::getNamedEntities("Player1")->front(); 
	Player* p2 = (Player*)EntityManager::getNamedEntities("Player2")->front();
	Player* p3 = (Player*)EntityManager::getNamedEntities("Player3")->front();
	Player* p4 = (Player*)EntityManager::getNamedEntities("Player4")->front();
	Player* currPlayer;
	//get health of all the players
	int p1Health = p1->getHealth();
	int p2Health = p2->getHealth();
	int p3Health = p3->getHealth();
	int p4Health = p4->getHealth();
	int movereset = 2;
	int shotsreset = 2;

	if(handler.isKeyDown(irr::KEY_RETURN) && !handler.wasKeyDown(KEY_RETURN))
	{
		y=y+1;
		if(y==5) y=1;
		p1->setMovementLeft(movereset);
		p1->setShotsLeft(shotsreset);
		p2->setMovementLeft(movereset);
		p2->setShotsLeft(shotsreset);
		p3->setMovementLeft(movereset);
		p3->setShotsLeft(shotsreset);
		p4->setMovementLeft(movereset);
		p4->setShotsLeft(shotsreset);
	}

	if (handler.isKeyDown(KEY_KEY_1)&&p1->isAlive()==true)//switch to player 1 if key pressed
	 {
		y=1;
		p1->setMovementLeft(movereset);
		p1->setShotsLeft(shotsreset);
	}
	else if (handler.isKeyDown(KEY_KEY_2)&&p2->isAlive()==true)//switch to player 2 if key pressed
	{
		y=2;
		p2->setMovementLeft(movereset);
		p2->setShotsLeft(shotsreset);
	}
	else if (handler.isKeyDown(KEY_KEY_3)&&p3->isAlive()==true)//switch to player 3 if key pressed
	{
		y=3;
		p3->setMovementLeft(movereset);
		p3->setShotsLeft(shotsreset);
	}
	else if (handler.isKeyDown(KEY_KEY_4)&&p4->isAlive()==true)//switch to player 4 if key pressed
	{
		y=4;
		p4->setMovementLeft(movereset);
		p4->setShotsLeft(shotsreset);
	}
	
	//----puts the players in the correct states depending on whose turn it is-------
	if(y == 1 && p1->isAlive()==true)
	{
		p1->movementState(); 
		p2->normalState();
		p3->normalState();
		p4->normalState();
	}
	else if (y==1 && p1->isAlive()==false) y=2;
	else if (y==2 && p2->isAlive()==true)
	{
		p2->movementState();
		p1->normalState();
		p3->normalState();
		p4->normalState();
	}
	else if (y==2 && p2->isAlive()==false) y=3;
	else if (y==3 && p3->isAlive()==true)
	{
		p3->movementState();
		p1->normalState();
		p2->normalState();
		p4->normalState();
	}
	else if (y==3 && p3->isAlive()==false) y=3;
	else if (y==4 && p4->isAlive()==true)
	{
		p4->movementState();
		p1->normalState();
		p2->normalState();
		p3->normalState();
	}
	else if (y==4 && p4->isAlive()==false) y=1;
	//------------------------------------------------------------------------------
	//-----------------text and end-------------------------------------------------
	//------------------text declarations-------------
////----------set text------------------------
	IGUIStaticText* text1;
	gui::IGUIWindow* msgBox;
	irr::gui::IGUIEnvironment* guienv = game.getDevice()->getGUIEnvironment();
	IGUIFont* font = guienv->getFont("Media/Textures/mycorrect.xml");
	std::wstringstream sstream;
	//--------------------------------------------
	
//-----------------------------------------------------------------------
	text1 = guienv->addStaticText(L"OMG YOU DEAD!", rect<s32>(500,310,1280,600),false);
	sstream.str(L"");
	text1->setText(sstream.str().c_str());
	
	text1->setOverrideColor(video::SColor(255,255,255,255));
	text1->setOverrideFont(font);		
	
	if(playersLeft <= 1 || (playersLeft == 2 && (p1->getLives() == 2 || p2->getLives() == 2 || p3->getLives() == 2 || p4->getLives() == 2 )))
	{
		if(p1->isAlive())currPlayer = p1;
		if(p2->isAlive())currPlayer = p2;
		if(p3->isAlive())currPlayer = p3;
		if(p4->isAlive())currPlayer = p4;
		text1->setRelativePosition(rect<s32>(500,310,1280,600));
		sstream<<"Player "<<currPlayer->getID()+1<<" Wins \n"<<"press esc to exit";
		text1->setText(sstream.str().c_str());
	}
	//------------------------------------------------------------------------------
	TurnHandler::checkHealth(p1, p1Health, p2, p2Health, p3, p3Health, p4, p4Health);//check health and check time
	TurnHandler::checkTime(p1,p2,p3,p4);
}

void TurnHandler::checkHealth(Player* player1, int health1,Player* player2, int health2, Player* player3, int health3,Player* player4, int health4)
{
	//check if health is below zero and if it is kill! 
	if (health1 <= 0 && player1->isAlive())
		{
			playersLeft = playersLeft - 1;
			player1->deadState();
			engine3->play2D("Media/Audio/death_1.ogg");
		}
	if (health2 <= 0 && player2->isAlive())
		{
			playersLeft = playersLeft - 1;
			player2->deadState();
			engine3->play2D("Media/Audio/death_2.ogg");
		}
	if (health3 <= 0 && player3->isAlive()) 
		{
			playersLeft = playersLeft - 1;
			player3->deadState();
			engine3->play2D("Media/Audio/death_3.ogg");
		}
	if (health4 <= 0 && player4->isAlive())
		{
			playersLeft = playersLeft - 1;
			player4->deadState();
			engine3->play2D("Media/Audio/death_4.ogg");
		}
}

void TurnHandler::checkTime(Player* player1, Player* player2,  Player* player3,Player* player4)//check if the player has been dead for 30 seconds and respawn or keep dead if lives <=0
{	
	irr::u32 tempTime = game.getDevice()->getTimer()->getRealTime();
	
//-----------------------------------------------------------------------
	int time = 15000;//Time to stay dead
	if(player1->getLives() <=0 && tempTime > player1->getdeathTime() + 1000)
	{
		player1->deadState();
		if(player1->getLives() ==0)
		{
			player1->setLives(-1); 
			engine3->play2D("Media/Audio/death_player1.ogg");
		}
	}
	else if (  tempTime > player1->getdeathTime() + time && !player1->isAlive()) player1->ReSpawnState();

	if(player2->getLives() <=0 && tempTime > player2->getdeathTime() + 1000)
	{
		player2->deadState();
		if(player2->getLives() ==0)
		{
			player2->setLives(-1); 
			engine3->play2D("Media/Audio/death_player2.ogg");
		}
	}
	else if (  tempTime > player2->getdeathTime() + time && !player2->isAlive()) player2->ReSpawnState();
	if(player3->getLives() <=0  && tempTime > player3->getdeathTime() + 1000)
	{
		player3->deadState();		
		if(player3->getLives() ==0)
		{
			player3->setLives(-1); 
			engine3->play2D("Media/Audio/death_player3.ogg");
		}
	}
	else if (  tempTime > player3->getdeathTime() + time && !player3->isAlive()) player3->ReSpawnState();
	if(player4->getLives() <=0  && tempTime > player4->getdeathTime() + 1000)	
	{
		player4->deadState();
		if(player4->getLives() ==0)
		{
			player4->setLives(-1); 
			engine3->play2D("Media/Audio/death_player4.ogg");
		}
	}
	else if (  tempTime > player4->getdeathTime() + time && !player4->isAlive()) player4->ReSpawnState();
}