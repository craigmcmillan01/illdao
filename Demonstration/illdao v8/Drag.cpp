#include "Drag.h"

using namespace irr::core;

void Drag::updateForce(Particle* particle, float frameTime)
{
	vector3df force = particle->velocity;

	float dragCoeff = force.getLength();
	if (dragCoeff <= 0.0f)
		return;
	dragCoeff = K1 * dragCoeff + K2 * dragCoeff * dragCoeff;

	force = force.normalize();
	force *= -dragCoeff;
	particle->force += force;
}

