#pragma once

#include "State.h"
#include "Pistol.h"
#include "Player.h"

using namespace irr::core;

class Bullet : public State<Pistol>
{
public:
	
	void execute(Pistol* owner, float frameTime );
	void collide(Pistol* owner, Player* player1, Player* player2,  Player* player3, Player* player4);
	void collideP1(Pistol* owner, Player* player, Player* shooter);
	void collideP2(Pistol* owner, Player* player, Player* shooter);
	void collideP3(Pistol* owner, Player* player, Player* shooter);
	void collideP4(Pistol* owner, Player* player, Player* shooter);
	void kill(Pistol* owner, Player* shooter);
};