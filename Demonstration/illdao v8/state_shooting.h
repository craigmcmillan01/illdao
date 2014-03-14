#pragma once

#include "State.h"
#include "Player.h"

using namespace irr::core;

class Shooting : public State<Player>
{
public:
	void execute(Player* owner, float frameTime);
};