#include "state_bullet.h"
#include "Player.h"
#include "Game.h"
#include "EntityManager.h"
#include<iostream>
#include <float.h>
#include <irrKlang.h>
using namespace irrklang;

ISoundEngine* engine2 = createIrrKlangDevice();				// start the sound engine with default parameters
	
void Bullet::execute(Pistol* owner, float frameTime)
{
	const f32 MovementSpeed = 120.0f;
	const f32 availableMovement = MovementSpeed * frameTime;
	vector3df nodePosition = owner->getParticle()->position;
	//set variables
	bool alive			= owner->isAlive();
	vector3df position	= owner->getParticle()->position;
	vector3df velocity	= owner->getParticle()->velocity;
	vector3df movement	= owner->getParticle()->movement;
	vector3df dest		= owner->getParticle()->destination;
	vector3df mPosition = owner->getParticle()->mousePosition;
	bool move_check		= owner->getParticle()->move_check;
	f32 temp			= owner->getParticle()->dist_trav;
	vector3df starPos	= owner->getParticle()->starPos;

	//create a ray through the camera with a plane around the node facing towards the camera
	scene::ISceneManager* smgr = game.getDevice()->getSceneManager();
	core::line3df ray = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(handler.getCurrentMouse().Position, game.getCamera()->GetcameraNode() ); 
	plane3df moveplane(0,0,0,0,1,0);	
	moveplane.getIntersectionWithLine(ray.start, ray.getVector(), mPosition);	//intersect the ray with a plane around the x,y
	vector3df toMousePosition(mPosition - position);

	//fire the node
	if (handler.getCurrentMouse().RightButton==true &&  handler.getPrevMouse().RightButton!=true)
	{
		starPos = nodePosition;
		dest = mPosition*vector3df(1,0,1);
		movement = (toMousePosition*vector3df(1,0,1)).normalize();
		move_check  = true;
	}
	if(move_check)
	{
		if(velocity == vector3df(0,0,0)) velocity = movement*availableMovement;
		nodePosition += velocity;
		owner->getNode()->setPosition(nodePosition);
		owner->getParticle()->position=(nodePosition);
		owner->getParticle()->velocity=velocity;
	
		f32 dx = starPos.X-nodePosition.X;
		f32 dy = starPos.Y-nodePosition.Y;
		f32 dz = starPos.Z-nodePosition.Z;
	
		temp = sqrt(dx*dx + dy*dy + dz*dz);		
	
		//Export the current state of the player back to the particle for the next iteration
		owner->getParticle()->movement=movement;
		owner->getParticle()->destination=dest;
		owner->getParticle()->mousePosition=mPosition;
		owner->getParticle()->move_check=move_check;
		owner->getParticle()->dist_trav=temp;
		owner->getParticle()->starPos=starPos;
		//##################################################################################################################
		//check if it hits a player
		Player* p1 = (Player*)EntityManager::getNamedEntities("Player1")->front();
		Player* p2 = (Player*)EntityManager::getNamedEntities("Player2")->front();
		Player* p3 = (Player*)EntityManager::getNamedEntities("Player3")->front();
		Player* p4 = (Player*)EntityManager::getNamedEntities("Player4")->front();
		
		if(p1->getCurrentState() == p1->getMovementState())
		{
			Bullet::collideP2(owner, p2, p1); 
			Bullet::collideP3(owner, p3, p1); 
			Bullet::collideP4(owner, p4, p1);
		}
		if(p2->getCurrentState() == p2->getMovementState())
		{
			Bullet::collideP1(owner, p1, p2);
			Bullet::collideP3(owner, p3, p2);
			Bullet::collideP4(owner, p4, p2);
		}
		if(p3->getCurrentState() == p3->getMovementState())
		{
			Bullet::collideP1(owner, p1, p3);
			Bullet::collideP2(owner, p2, p3);
			Bullet::collideP4(owner, p4, p3);
		}
		if(p4->getCurrentState() == p4->getMovementState())
		{
			Bullet::collideP1(owner, p1, p4);
			Bullet::collideP2(owner, p2, p4);
			Bullet::collideP3(owner, p3, p4);
		}
		//##################################################################################################################
		//check the range
		if (owner->getParticle()->dist_trav > 75) // kill when it goes beyond 25
		{
			//engine2->stopAllSounds();
			Bullet::kill(owner, p1);
		}
	}
}

void Bullet::collideP1(Pistol* owner, Player* p1, Player* shot)//check if player 1 gets shot
{
	aabbox3df nodeBox = owner->getNode()->getTransformedBoundingBox();
	aabbox3df p1Box = p1->getNode()->getTransformedBoundingBox();
	if (p1Box.intersectsWithBox(nodeBox)  )
	{	
		p1->setHealth(p1->getHealth()-1);
		engine2->play2D("Media/Audio/pain_1.ogg");

	}
}
void Bullet::collideP2(Pistol* owner, Player* p2, Player* shot)//check if player 2 gets shot
{
	aabbox3df nodeBox = owner->getNode()->getTransformedBoundingBox();
	aabbox3df p2Box = p2->getNode()->getTransformedBoundingBox();
	if (p2Box.intersectsWithBox(nodeBox)  )
	{	
		p2->setHealth(p2->getHealth()-1);
		engine2->play2D("Media/Audio/pain_2.ogg");
	}
}
void Bullet::collideP3(Pistol* owner, Player* p3, Player* shot)//check if player 3 gets shot
{
	aabbox3df nodeBox = owner->getNode()->getTransformedBoundingBox();
	aabbox3df p3Box = p3->getNode()->getTransformedBoundingBox();
	if (p3Box.intersectsWithBox(nodeBox)  )
	{	
		p3->setHealth(p3->getHealth()-1);
		engine2->play2D("Media/Audio/pain_3.ogg");
	}
}
void Bullet::collideP4(Pistol* owner, Player* p4, Player* shot)//check if player 4 gets shot
{
	aabbox3df nodeBox = owner->getNode()->getTransformedBoundingBox();
	aabbox3df p4Box = p4->getNode()->getTransformedBoundingBox();
	if (p4Box.intersectsWithBox(nodeBox)  )
	{	
		p4->setHealth(p4->getHealth()-1);
		engine2->play2D("Media/Audio/pain_4.ogg");
	}
}

void Bullet::kill(Pistol* owner, Player* shot)//kill the bullet and reset the values
{
	owner->setAlive(false);
	owner->getNode()->setVisible(false);
	owner->getParticle()->movement=vector3df(0,0,0);
	owner->getParticle()->destination=vector3df(0,0,0);
	owner->getParticle()->mousePosition=vector3df(0,0,0);
	owner->getParticle()->move_check=false;
	owner->getParticle()->dist_trav=0;
	owner->getParticle()->position=shot->getNode()->getPosition();
	owner->getNode()->setPosition(shot->getNode()->getPosition());
	owner->getParticle()->starPos=vector3df(0,0,0);
	owner->getParticle()->velocity=vector3df(0,0,0);
	owner->getParticle()->acceleration=vector3df(0,0,0);
}