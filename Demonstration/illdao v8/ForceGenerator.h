#pragma once

#include "Particle.h"

class ForceGenerator
{
public:
	virtual ~ForceGenerator() { }
	virtual void updateForce(Particle* particle, float frameTime) = 0;
};