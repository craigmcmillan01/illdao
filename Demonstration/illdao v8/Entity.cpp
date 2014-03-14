#include "Entity.h"
#include "EntityManager.h"

Entity::Entity(int id,irr::scene::IAnimatedMeshSceneNode* node, std::string name) : id(id), name(name), node(node), alive(true)
{
	EntityManager::registerEntity(this);
}

Entity::~Entity()
{
	EntityManager::removeEntity(this);
}