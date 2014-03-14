#include "ForceRegistry.h"

using namespace std;

hash_map<Particle*, std::list<ForceGenerator*>*> ForceRegistry::registry = hash_map<Particle*, std::list<ForceGenerator*>*>();
ForceRegistry* ForceRegistry::instance = 0;

void ForceRegistry::add(Particle* particle, ForceGenerator* force)
{
	auto iter = registry.find(particle);
	if (iter == registry.end())
	{
		std::list<ForceGenerator*>* list = new std::list<ForceGenerator*>();
		list->push_back(force);
		registry[particle] = list;
	}
	else
		iter->second->push_back(force);
}

void ForceRegistry::remove(Particle* particle, ForceGenerator* force)
{
	registry[particle]->remove(force);
}

void ForceRegistry::clear()
{
	auto iter = registry.begin();
	for (; iter != registry.end(); ++iter)
	{
		auto listIter = iter->second->begin();
		for (; listIter != iter->second->end(); ++listIter)
		{
			delete *listIter;
			*listIter = 0;
		}
		delete iter->second;
		iter->second = 0;
	}
}

void ForceRegistry::update(float deltaTime)
{
	auto iter = registry.begin();
	for (; iter != registry.end(); ++iter)
	{
		auto listIter = iter->second->begin();
		for (; listIter != iter->second->end(); ++listIter)
			(*listIter)->updateForce(iter->first, deltaTime);
	}
}