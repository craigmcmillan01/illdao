#pragma once

#include <hash_map>
#include <list>
#include "Particle.h"
#include "ForceGenerator.h"

using namespace std;

class ForceRegistry
{
private:
	static hash_map<Particle*, std::list<ForceGenerator*>*> registry;
	static ForceRegistry* instance;
	ForceRegistry() { }
public:
	~ForceRegistry() { clear(); }
	static void initialise() { }
	static void update(float deltaTime);
	static void add(Particle* particle, ForceGenerator* force);
	static void remove (Particle* particle, ForceGenerator* force);
	static void clear();
};