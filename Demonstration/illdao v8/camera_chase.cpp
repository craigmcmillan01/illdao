#include "camera_chase.h"
#include "Game.h"
#include <iostream>

using namespace irr::core;
using namespace irr::scene;

void ChaseCamera::initialise()
{
	cameraNode = game.getDevice()->getSceneManager()->addCameraSceneNode();
	springiness = 1.0f;
}

void ChaseCamera::update(float deltaTime)
{
		if (handler.isKeyDown(KEY_NUMPAD8)) 
		{
			followTargetRotation.Z = -1*deltaTime;
			followTargetRotation.X = 1*deltaTime;		
		}
		 if (handler.wasKeyDown(KEY_NUMPAD8)!=true)
			 {
				 followTargetRotation.Z = 0;
				 followTargetRotation.X = 0;
		 }

		if (handler.isKeyDown(KEY_NUMPAD4)) followTargetRotation.Y = 10*deltaTime;
		if (handler.wasKeyDown(KEY_NUMPAD4)!=true) followTargetRotation.Y = 0;

		if (handler.isKeyDown(KEY_NUMPAD6)) followTargetRotation.Y = -10*deltaTime;
		if (handler.wasKeyDown(KEY_NUMPAD6)!=true) followTargetRotation.Y = 0;
		
		if (handler.isKeyDown(KEY_NUMPAD5)) followTargetRotation.X = -10*deltaTime;
		if (handler.wasKeyDown(KEY_NUMPAD5)!=true) followTargetRotation.X = 0;
					
					//cameraNode->setPosition(cameraNode->getPosition() + 20*deltaTime);

					//game.getCamera()->setPosition(cameraNode->getPosition() + 20*deltaTime);

		 vector3df zoom(followTargetPosition - cameraNode->getPosition());
		 //vector3df zoom(mPosition - position);

	if (handler.isKeyDown(KEY_NUMPAD7))
		positionOffset+=zoom*deltaTime;
	if (handler.isKeyDown(KEY_NUMPAD9))
		positionOffset-=zoom*deltaTime;
	if (handler.isKeyDown(KEY_NUMPAD0))
		positionOffset = vector3df(0.0f, 40.0f,0.0f);
	//std::cout<<positionOffset.X<<" , "<<positionOffset.Y<<" , "<<positionOffset.Z<<" \n"; //debug to find values
	
	vector3df combinedRotation = followTargetRotation + relativeCameraRotation;
	matrix4 mat = IdentityMatrix;
	mat.setRotationRadians(combinedRotation);
	mat.transformVect(positionOffset);
	vector3df desiredPosition = followTargetPosition + positionOffset;
	position = lerp<vector3df>(position, desiredPosition, springiness);
	mat.transformVect(targetOffset);
	target = followTargetPosition + targetOffset;
	up = vector3df(0, 1, 0);
	mat.transformVect(up);
	cameraNode->setPosition(position);
	cameraNode->setTarget(target);
	cameraNode->setUpVector(up);
}

void ChaseCamera::move(vector3df newFollowTargetPosition, vector3df newFollowTargetRotation)
{
	followTargetPosition = newFollowTargetPosition;
	followTargetRotation = newFollowTargetRotation;
}

void ChaseCamera::rotate(vector3df deltaRotation)
{
	relativeCameraRotation += deltaRotation;
}
