#pragma once

#include <irrlicht.h>

class Camera
{
protected:
	irr::scene::ICameraSceneNode* cameraNode;
	irr::core::vector3df position;
	irr::core::vector3df target;
	irr::core::vector3df up;
public:
	Camera() {}
	virtual ~Camera() {}
	virtual void initialise() = 0;
	virtual void update(float deltaTime) = 0;
	irr::core::vector3df getPosition() const { return position; }
	void setPosition(irr::core::vector3df value) { position = value; }
	irr::core::vector3df getTarget() const{ return target; }
	void setTarget(irr::core::vector3df value) { target = value; }
	irr::core::vector3df getUp() const { return up; }
	void setUp(irr::core::vector3df value) { target = value; } 
	irr::scene::ICameraSceneNode* GetcameraNode() const{return cameraNode;}
};