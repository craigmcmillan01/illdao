#pragma once

#include <hash_map>
#include "Entity.h"

class EntityManager
{
private:
	static int nextID;
	static std::hash_map<int, Entity*> entities;//old line
	static std::hash_map<std::string, std::list< Entity*>> namedEntities;
	EntityManager();
	~EntityManager();
	static EntityManager* instance;
public:
	static void initialise();
	static void loadContent();
	static void update(float deltaTime);
	static void unloadContent();
	static void registerEntity(Entity* entity);
	static void removeEntity(Entity* entity);
	static Entity* getEntity(int id);
	static std::list<Entity*>* getNamedEntities(const std::string& name);
};

