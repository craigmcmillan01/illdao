#pragma once

#include "State.h"
#include "Player.h"

using namespace irr::core;

class ReSpawn : public State<Player>
{
public:
	void execute(Player* owner, float frameTime);
};