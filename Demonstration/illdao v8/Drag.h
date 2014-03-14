#pragma once

#include "ForceGenerator.h"

class Drag : public ForceGenerator
{
private:
	float K1;
	float K2;
public: 
	Drag(float K1, float K2) : K1(K1), K2(K2) {}
	virtual ~Drag () {}
	void updateForce(Particle* particle, float frameTime);
};

