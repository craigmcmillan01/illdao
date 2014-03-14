#pragma once

#include <irrlicht.h>
#include "ForceGenerator.h"

using namespace irr::core;

class Gravity : public ForceGenerator
{
private:
	vector3df gravity;
public:
	Gravity(const vector3df gravity) : gravity(gravity) { }
	virtual ~Gravity() {}
	void updateForce(Particle* particle, float frameTime);
};