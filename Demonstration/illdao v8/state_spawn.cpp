#include "state_spawn.h"
#include "EntityManager.h"
#include "Game.h"

using namespace irr::core;

void SpawnState::execute(Player* owner, float deltaTime)
{
	Player* p1 = (Player*)EntityManager::getNamedEntities("Player1")->front(); 
	Player* p2 = (Player*)EntityManager::getNamedEntities("Player2")->front();
	Player* p3 = (Player*)EntityManager::getNamedEntities("Player3")->front();
	Player* p4 = (Player*)EntityManager::getNamedEntities("Player4")->front();
	
	//set spawning position
	p1->getNode()->setPosition(vector3df(-10,1,-90));
	p2->getNode()->setPosition(vector3df(-70,1,-90));
	p3->getNode()->setPosition(vector3df( 70,1,40));
	p4->getNode()->setPosition(vector3df(-10,1,40));
	int speed = 8;
	p1->getNode()->setAnimationSpeed(speed);
	p2->getNode()->setAnimationSpeed(speed);
	p3->getNode()->setAnimationSpeed(speed);
	p4->getNode()->setAnimationSpeed(speed);
	p1->getNode()->setFrameLoop(183,204);
	p2->getNode()->setFrameLoop(183,204);
	p3->getNode()->setFrameLoop(205,249);
	p4->getNode()->setFrameLoop(250,299);
	
	//set particle position
	p1->getParticle()->position = p1->getNode()->getPosition();
	p2->getParticle()->position = p2->getNode()->getPosition();
	p3->getParticle()->position = p3->getNode()->getPosition();
	p4->getParticle()->position = p4->getNode()->getPosition();
		
	//set textures
	p2->getNode()->setMaterialTexture( 0, game.getDevice()->getVideoDriver()->getTexture("Media/Textures/nskinrd.jpg") );
	p2->getNode()->setMaterialType( video::EMT_SOLID );

	p3->getNode()->setMaterialTexture( 0, game.getDevice()->getVideoDriver()->getTexture("Media/Textures/nskinbl.jpg") );
	p3->getNode()->setMaterialType( video::EMT_SOLID );
		
	p4->getNode()->setMaterialTexture( 0, game.getDevice()->getVideoDriver()->getTexture("Media/Textures/nskingr.jpg") );
	p4->getNode()->setMaterialType( video::EMT_SOLID );
	
	//-----set initial health values and life values----
	p1->setHealth(10);
	p2->setHealth(10);
	p3->setHealth(10);
	p4->setHealth(10);

	p1->setLives(2);
	p2->setLives(2);
	p3->setLives(2);
	p4->setLives(2);
	//----set starting movement and shots-----
	p1->setMovementLeft(2);
	p2->setMovementLeft(2);
	p3->setMovementLeft(2);
	p4->setMovementLeft(2);

	p1->setShotsLeft(2);
	p2->setShotsLeft(2);
	p3->setShotsLeft(2);
	p4->setShotsLeft(2);
	//--------------------------------------------
}