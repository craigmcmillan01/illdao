#include "state_shooting.h"
#include "Pistol.h"
#include "Game.h"
#include "EntityManager.h"
#include "MessageHandler.h"
#include <iostream>

void Shooting::execute(Player* owner, float frameTime)//passes a message to fire a bullet
{
	//std::list<Pistol*>* pistol = (std::list<Pistol*>*)EntityManager::getNamedEntities("Pistol")->front();
	//std::list<Pistol*>::iterator iter = pistol->begin();
	
	std::list<Entity*>* entities = EntityManager::getNamedEntities("Pistol");
	std::list<Entity*>::iterator iter = entities->begin();
	
	for (; iter != entities->end(); ++iter)
	//for (; iter != pistol->end(); ++iter)
	{		
		if (!(*iter)->isAlive())
		{
			irr::core::vector3df* pos = new irr::core::vector3df(owner->getNode()->getPosition());//was owner
			Message message((*iter), "Fire", pos);
			//(*iter)->BulletState();
			MessageHandler::sendMessage(message);
			//std::cout<<"MESSAGE SENT!!!!\n";//debug statement
			break;			
		}
	}
}