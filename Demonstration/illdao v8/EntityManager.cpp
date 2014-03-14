#include "EntityManager.h"

int EntityManager::nextID = 0;
EntityManager* EntityManager::instance = new EntityManager();
std::hash_map<int, Entity*> EntityManager::entities = std::hash_map<int, Entity*>();//old line
std::hash_map<std::string, std::list< Entity*>> EntityManager::namedEntities = std::hash_map<std::string, std::list< Entity*>>();//new line

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
	std::hash_map<int, Entity*>::iterator iter = entities.begin();
	for (; iter != entities.end(); ++iter)
	{
		iter->second->unloadContent();
		delete iter->second;
		iter->second = 0;
	}
	entities.clear();
}

void EntityManager::initialise()
{
	std::hash_map<int, Entity*>::iterator iter = entities.begin();
	for (; iter != entities.end(); ++iter)
		iter->second->initialise();
}

void EntityManager::loadContent()
{
	std::hash_map<int, Entity*>::iterator iter = entities.begin();
	for (; iter != entities.end(); ++iter)
		iter->second->loadContent();
}

void EntityManager::update(float deltaTime)
{
	std::hash_map<int, Entity*>::iterator iter = entities.begin();
	for (; iter != entities.end(); ++iter)
		iter->second->update(deltaTime);
}

void EntityManager::unloadContent()
{
	std::hash_map<int, Entity*>::iterator iter = entities.begin();
	for (; iter != entities.end(); ++iter)
		iter->second->unloadContent();
}

void EntityManager::registerEntity(Entity* entity)
{
	if (entity->getID() == -1)
	{
		while (entities.find(EntityManager::nextID) != entities.end())
			++EntityManager::nextID;
		entity->setID(nextID);
	}
	else if (entities.find(entity->getID()) != entities.end())
		throw; // Entity of ID exists. Throw exception
	entities[entity->getID()] = entity;

	if (entity->getName() != "")
	{
		std::hash_map<std::string, std::list<Entity*>>::iterator iter = namedEntities.find(entity->getName());
		if (iter == namedEntities.end())
		{
			//list doest exist. add new list and add entity to it 
			std::list<Entity*> entities;
			entities.push_back(entity);
			namedEntities[entity->getName()] = entities;
		}
		else
			//add to existing list
			iter->second.push_back(entity);
	}
}

void EntityManager::removeEntity(Entity* entity)
{
	std::hash_map<int, Entity*>::iterator iter = entities.find(entity->getID());
	if (iter != entities.end())
		entities.erase(iter);
	if (entity->getName() != "")
	{
		//find the list of entities, and remove this entity from it
		std::hash_map<std::string, std::list<Entity*>>::iterator iter = namedEntities.find(entity->getName());
		iter->second.remove(entity);
	}

}

Entity* EntityManager::getEntity(int id)
{
	std::hash_map<int, Entity*>::iterator iter = entities.find(id);
	if (iter != entities.end())
		return iter->second;
	return 0; // NULL
}

std::list<Entity*>* EntityManager::getNamedEntities(const std::string& name)
{
	std::hash_map<std::string, std::list<Entity*>>::iterator iter = namedEntities.find(name);
	if (iter != namedEntities.end())
		return &(iter->second);
	else
		return 0;
}