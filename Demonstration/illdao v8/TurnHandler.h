#pragma once

//#include "MessageHandler.h"
#include "Entity.h"
#include "Player.h"
#include <irrlicht.h>

class TurnHandler : public Entity
{
public:
	TurnHandler() : Entity(-1, 0, "TurnHandler") { }
	~TurnHandler() { } 
	void initialise();
	void loadContent();
	//static void update(float deltaTime);
	void update(float deltaTime);
	void unloadContent() { }
	void handleMessage(const Message& message);
	void checkHealth(Player* player1, int health1,Player* player2, int health2, Player* player3, int health3,Player* player4, int health4);
	void checkTime(Player* player1, Player* player2,  Player* player3,Player* player4);
};