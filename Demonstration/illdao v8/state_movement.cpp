#include "state_movement.h"
#include "Game.h"
#include <irrKlang.h>
#include <iostream>

using namespace irrklang;

ISoundEngine* engine = createIrrKlangDevice();				// start the sound engine with default parameters
void Movement::execute(Player* owner, float frameTime)
{	
	const f32 MovementSpeed = 25.0f;//set variables
	double PI = 3.14159265;
	const f32 availableMovement = MovementSpeed * frameTime;
	vector3df nodePosition = owner->getParticle()->position;

	vector3df position	= owner->getParticle()->position;
	vector3df velocity	= owner->getParticle()->velocity;
	vector3df movement	= owner->getParticle()->movement;
	vector3df dest		= owner->getParticle()->destination;
	vector3df mPosition = owner->getParticle()->mousePosition;
	bool move_check		= owner->getParticle()->move_check;
	float angle			= owner->getParticle()->facing;
	
	scene::ISceneManager* smgr = game.getDevice()->getSceneManager();	
	core::line3df ray = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates( handler.getCurrentMouse().Position, game.getCamera()->GetcameraNode() ); 
	plane3df moveplane(0,0,0,0,1,0);
	moveplane.getIntersectionWithLine(ray.start, ray.getVector(), mPosition);	
	vector3df toMousePosition(mPosition - position); //Calculate vector between current location and destination

	if (handler.getCurrentMouse().LeftButton==true &&  handler.getPrevMouse().LeftButton!=true)
	{
		if (owner->getMovementLeft() > 0)//if player still has movement turns left then move
		{
		float X = mPosition.X - position.X;
		float Y = mPosition.Z - position.Z;
		dest = mPosition*vector3df(1,0,1);
		movement = (toMousePosition*vector3df(1,0,1)).normalize();
		angle = (atan2(X,Y)*180/PI); //Calculate the angle needed to face destination
		move_check  = true;	
		owner->setMovementLeft(owner->getMovementLeft() - 1);
		//owner->getNode()->setFrameLoop(0,13);
		owner->getNode()->setFrameLoop(158,164);
		//std::cout<<"movement left "<<owner->getMovementLeft()<<" \n"<<"shots left "<<owner->getShotsLeft()<<" \n ";//debug statement
		engine->play2D("Media/Audio/walk.wav", true);
		}
		else//dont move and display message
		{
			move_check = false;
			//std::cout<<"sorry no movement left, please switch turn\n";
		}
	}
	if(move_check)
	{
		vector3df distance((dest - position)*vector3df(1,0,1));
		if(velocity == vector3df(0,0,0)) velocity = movement*availableMovement; //if the player was not already moving give them a velocity
		
		nodePosition = nodePosition + velocity;
		nodePosition.Y = owner->getNode()->getPosition().Y;
		
		owner->getNode()->setPosition(nodePosition);
		owner->getNode()->setRotation(vector3df(0.0f, angle,0.0f));		
		owner->getParticle()->position=nodePosition;
		owner->getParticle()->velocity=velocity;

		if(distance.getLength() <= availableMovement)
		{
			engine->stopAllSounds();
			owner->getNode()->setFrameLoop(183,204);
			nodePosition = dest;
			move_check  = false;
			owner->getParticle()->velocity=vector3df(0,0,0);
		}
		//Export the current state of the player back to the particle for the next iteration
		owner->getParticle()->facing=angle;
		owner->getParticle()->movement=movement;
		owner->getParticle()->destination=dest;
		owner->getParticle()->mousePosition=mPosition;
		owner->getParticle()->move_check=move_check;
		owner->getParticle()->velocity=vector3df(0,0,0);
		//#####################################################################################
	} 
}