#pragma once

#include <string>
#include <irrlicht.h>
using namespace irr;
using namespace core;

struct Particle
{
	vector3df acceleration;
	float damping;
	vector3df force;
	float mass;
	vector3df position;
	vector3df velocity;
	float temp;
	vector3df movement;
	vector3df destination;
	vector3df mousePosition;
	float facing;
	bool move_check;
	float dist_trav;
	vector3df starPos;

	Particle(vector3df position, vector3df velocity, float mass) 
		: position(position), velocity(velocity), mass(mass), damping(1.0f), force(0.0f, 0.0f, 0.0f), acceleration(0.0f, 0.0f, 0.0f)
	{}

	void update(float deltaTime)
	{

	}
};