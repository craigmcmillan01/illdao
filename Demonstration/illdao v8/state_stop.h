#pragma once

#include "State.h"
#include "Pistol.h"

using namespace irr::core;

class BulletStop : public State<Pistol>
{
public:
	void execute(Pistol* owner, float frameTime);
};