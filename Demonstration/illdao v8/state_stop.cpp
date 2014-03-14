#include "state_stop.h"
#include "Game.h"
#include "EntityManager.h"
#include <iostream>


void BulletStop::execute(Pistol* owner, float frameTime)
{
		owner->setAlive(false);
	owner->getNode()->setVisible(false);
	owner->getParticle()->facing=0;
	owner->getParticle()->movement=vector3df(0,0,0);
	owner->getParticle()->destination=vector3df(0,0,0);
	owner->getParticle()->mousePosition=vector3df(0,0,0);
	owner->getParticle()->move_check=false;
	owner->getParticle()->dist_trav=0;
	/*owner->getParticle()->position=shot->getNode()->getPosition();
	owner->getNode()->setPosition(shot->getNode()->getPosition());
	std::cout<<"shot"<<shot->getNode()->getPosition().X<<" , "<<shot->getNode()->getPosition().Y<<" , "<<shot->getNode()->getPosition().Z<<" \n ";*/
	owner->getParticle()->position=vector3df(0,0,0);
	owner->getParticle()->starPos=vector3df(0,0,0);
	owner->getParticle()->velocity=vector3df(0,0,0);
	owner->getParticle()->acceleration=vector3df(0,0,0);
}