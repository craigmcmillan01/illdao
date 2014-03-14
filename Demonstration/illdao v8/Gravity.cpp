#include <limits>
#include "Gravity.h"

void Gravity::updateForce(Particle* particle, float frameTime)
{
	if (particle->mass == std::numeric_limits<float>::infinity())
		return;
	particle->force += gravity * particle->mass;
}