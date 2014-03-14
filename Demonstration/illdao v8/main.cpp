#pragma comment(lib, "Irrlicht")
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

#include <iostream>
#include <string>
#include <sstream>
#include <irrKlang.h>
#include "Game.h"
#include "Player.h"
#include "camera_chase.h"
#include "Pistol.h"
#include "EntityManager.h"
#include "TurnHandler.h"
#include "Map.h"

using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;
using namespace irrklang;
using namespace irr::gui;

int main()
{
	Player player_1("1"); // initialise the entities and map for the game
	Player player_2("2");
	Player player_3("3");
	Player player_4("4");
	Pistol pistol[1];
	Map map;
	TurnHandler turnHandler;

	int screenx = 1280;
	int screeny = 720;
	game.setDimension(irr::core::dimension2d<irr::u32>(screenx, screeny));	//and dimension

	ChaseCamera* camera = new ChaseCamera();	//game camera
	camera->setPositionOffset(vector3df(0.0f, 120.0f, 0.0f));	//
	
	game.setCamera(camera);										
	game.initialise();	//initialise 
	game.loadContent();	//and load the content for the game

	//------------------set timing variables------------------------
	irr::u32 prevTime = game.getDevice()->getTimer()->getRealTime();
	irr::u32 currTime;
	irr::u32 tempTime = game.getDevice()->getTimer()->getRealTime();;
	irr::f32 deltaTime;
	//--------------------------------------------------------------
	//--------- start the sound engine with default parameters------
	IVideoDriver *driver = game.getDevice()->getVideoDriver();
	ISoundEngine* engine = createIrrKlangDevice();				
	if (!engine)  return 0; // error starting up the engine
	engine->play2D("Media/Audio/lab_1.ogg", true);
	engine->play2D("Media/Audio/welcome_1.ogg");
	int lastFPS = -1;
	//--------------------------------------------------------------
	//--------------------set mouse and light-----------------------
	//Decides whether to show mouse cursor
	game.getDevice()->getCursorControl()->setVisible(true);
			
	//the light
	scene::ILightSceneNode * light = game.getDevice()->getSceneManager()->addLightSceneNode(0, core::vector3df(-60,100,400),
		video::SColorf(1.0f,1.0f,1.0f,1.0f), 600.0f);
	//--------------------------------------------------------------
	//----------set text------------------------
	IGUIStaticText* text;
	IGUIStaticText* switchText;
	irr::gui::IGUIEnvironment* guienv = game.getDevice()->getGUIEnvironment();
	text = guienv->addStaticText(L"current player = health = moves left = turns left =", rect<s32>(1000,1700,218,340),false,true,0,-1,true);
	switchText = guienv->addStaticText(L" ", rect<s32>(400,310,1280,600),false);
	IGUIFont* font = guienv->getFont("Media/Textures/myfont.xml");
	IGUIFont* font1 = guienv->getFont("Media/Textures/mycorrect.xml");
	//text->setOverrideColor(video::SColor(255,255,255,255));
	switchText->setOverrideColor(video::SColor(255,255,255,255));
	text->setOverrideFont(font);
	switchText->setOverrideFont(font1);
	//--------------------------------------------			 

	//##############################################################################################################
	//#### 									--MAIN--GAME--LOOP--												####
	//##############################################################################################################
	while (game.getDevice()->run())
	{

		currTime = game.getDevice()->getTimer()->getRealTime();
		deltaTime = (float)(currTime - prevTime) / 1000.0f;
		if(handler.isKeyDown(KEY_ESCAPE)) break;	//End the program when ESC is pushed
		
		//----------------Code for switching the camera between the players------------
		Player* p1 = (Player*)EntityManager::getNamedEntities("Player1")->front();
		Player* p2 = (Player*)EntityManager::getNamedEntities("Player2")->front();
		Player* p3 = (Player*)EntityManager::getNamedEntities("Player3")->front();
		Player* p4 = (Player*)EntityManager::getNamedEntities("Player4")->front();
		Player* currentPlayer;
		//Change camera position to next player position and set current player to shooting player
		vector3df x;
		std::wstringstream sstream;
		std::wstringstream astream;
		if(p1->getCurrentState() == p1->getMovementState())
		{
			camera->SetFollowTargetPosition(p1->getNode()->getPosition()+vector3df(0,6,0));
			x = p1->getNode()->getPosition();
			//--------text----------
			astream.str(L"");
			switchText->setText(astream.str().c_str());
			text->setRelativePosition(rect<s32>(1100,0,1280,120));
			sstream<<"Current Player = Player 1, Health = "<<p1->getHealth()<<", Shots Left = "<<p1->getShotsLeft()<<", Movement Left = "<<p1->getMovementLeft();
			//sstream<<"Current Player = Player 1\nHealth = "<<p1->getHealth()<<"\nShots Left = "<<p1->getShotsLeft()<<"\nMovement Left = "<<p1->getMovementLeft();
			text->setText(sstream.str().c_str());
			if(p1->getMovementLeft() <= 0 && p1->getShotsLeft() <=0)
			{
				astream<<"Press Enter To Switch Player!";
				//astream<<"FUCK C++!!!!";
				switchText->setText(astream.str().c_str());
			}
			//------------------------
			currentPlayer = p1;
		}
		if(p2->getCurrentState() == p2->getMovementState())
		{
			camera->SetFollowTargetPosition(p2->getNode()->getPosition()+vector3df(0,6,0));
			x = p2->getNode()->getPosition();
			//--------text----------
			astream.str(L"");
			switchText->setText(astream.str().c_str());
			text->setRelativePosition(rect<s32>(1100,0,1280,120));
			sstream<<"Current Player = Player 2\nHealth = "<<p2->getHealth()<<"\nShots Left = "<<p2->getShotsLeft()<<"\nMovement Left = "<<p2->getMovementLeft();
			text->setText(sstream.str().c_str());
			if(p2->getMovementLeft() <= 0 && p2->getShotsLeft() <=0)
			{
				astream<<"Press Enter To Switch Player!";
				switchText->setText(astream.str().c_str());
			}
			//------------------------
			currentPlayer = p2;
		}
		if(p3->getCurrentState() == p3->getMovementState())
		{
			camera->SetFollowTargetPosition(p3->getNode()->getPosition()+vector3df(0,6,0));
			x = p3->getNode()->getPosition();
			//--------text----------
			astream.str(L"");
			switchText->setText(astream.str().c_str());
			text->setRelativePosition(rect<s32>(1100,0,1280,120));
			sstream<<"Current Player = Player 3, Health = "<<p3->getHealth()<<", Shots Left = "<<p3->getShotsLeft()<<", Movement Left = "<<p3->getMovementLeft();
			text->setText(sstream.str().c_str());
			if(p3->getMovementLeft() <= 0 && p3->getShotsLeft() <=0)
			{
				astream<<"Press Enter To Switch Player!";
				switchText->setText(astream.str().c_str());
			}
			//------------------------
			currentPlayer = p3;
		}
		if(p4->getCurrentState() == p4->getMovementState())
		{
			camera->SetFollowTargetPosition(p4->getNode()->getPosition()+vector3df(0,6,0));
			x = p4->getNode()->getPosition();
			//--------text----------
			astream.str(L"");
			switchText->setText(astream.str().c_str());
			text->setRelativePosition(rect<s32>(1100,0,1280,120));
			sstream<<"Current Player = Player 4\nHealth = "<<p4->getHealth()<<"\nShots Left = "<<p4->getShotsLeft()<<"\nMovement Left = "<<p4->getMovementLeft();
			text->setText(sstream.str().c_str());
			if(p4->getMovementLeft() <= 0 && p4->getShotsLeft() <=0)
			{
				astream<<"Press Enter To Switch Player!";
				switchText->setText(astream.str().c_str());
			}
			//------------------------
			currentPlayer = p4;
		}

		//-----------------fire a bullet-------------------------------------------------------------------
		if (handler.getCurrentMouse().RightButton==true &&  handler.getPrevMouse().RightButton!=true)
		{
			int i=0;
			if (pistol[i].isAlive() == false && currentPlayer->getShotsLeft() > 0)
				{
					engine->play2D("Media/Audio/shot007.wav");
					//x = (x*vector3df(1,0,1)+vector3df(0,5,0));
					x = vector3df(x.X, (x.Y+5), x.Z);
					pistol[i].getParticle()->position = x;
					pistol[i].getNode()->setPosition(x) ;
					pistol[i].setAlive(true);
					pistol[i].getNode()->setVisible(true);
					pistol[i].BulletState();
					currentPlayer->setShotsLeft(currentPlayer->getShotsLeft() - 1);
				}
			else std::cout<<"no shots left, move or switch turn"<< currentPlayer->getShotsLeft()<<" \n ";
		}
		
		//---------------------------------------------------------------------------------------------------
		game.update(deltaTime);	//update	
		game.render();			//and draw to screen
		prevTime = currTime;	//update previous time	
		//---------------------------------------------------------------------------------------------------
		if (driver->getFPS() != lastFPS)//draw fps to the window caption
		{
			lastFPS = driver->getFPS();
			core::stringw tmp = L"Illdao - (FPS: ";
			tmp += lastFPS;
			tmp += ")";
			game.getDevice()->setWindowCaption(tmp.c_str());
		}
	}
	//##############################################################################################################
	//#### 									--MAIN--OF--LOOP--													####
	//##############################################################################################################
	engine->drop(); // delete engine
	game.unloadContent();	//unload
	game.shutdown();		//and shutdown
}