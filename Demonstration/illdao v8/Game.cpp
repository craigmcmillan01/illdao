#include <iostream>
#include <time.h>
#include "Game.h"
#include "EntityManager.h"
#include "Message.h"
#include "MessageHandler.h"
#include "ForceRegistry.h"
#include "TurnHandler.h"
#include "camera_chase.h"

GameEngine::Game game = GameEngine::Game();
KeyHandler keyHandler = KeyHandler();
InputHandler handler = InputHandler();

namespace GameEngine
{
	void Game::initialise()
	{
		device = irr::createDevice(irr::video::EDT_DIRECT3D9,
			dimensions,
			16,
			false,
			false,
			true,
			&handler);

		if (!device)
		{
			std::cerr << "Error creating device" << std::endl;
			exit(1);
		}
		device->setWindowCaption(caption.c_str());
		EntityManager::initialise();
		camera->initialise();
		MessageHandler::init();
		ForceRegistry::initialise();
		srand(time(NULL));


		device->getGUIEnvironment()->addStaticText(L"Welcome to Illdao!\nLeft Click to move to that location.\nRight Click to shoot in that direction.\nYou only have two shots and two chances to move!\nPress the Enter key to switch player\nGood Luck ! :)\n",
			core::rect<s32>(0,0,218,170),false,true,0,-1,true)->setOverrideFont(device->getGUIEnvironment()->getFont("Media/Textures/myfont.xml"));
	}

	void Game::loadContent() { EntityManager::loadContent(); }

	void Game::update(float frameTime)
	{
		EntityManager::update(frameTime);
		handler.update();
		camera->update(frameTime);
		ForceRegistry::update(frameTime);
		MessageHandler::update();
	}

	void Game::render()
	{
		device->getVideoDriver()->beginScene();
		device->getSceneManager()->drawAll();
		device->getGUIEnvironment()->drawAll();
		device->getVideoDriver()->endScene();
	}

	void Game::unloadContent() { EntityManager::unloadContent(); }
	void Game::shutdown() { device->drop(); }
}