#include <iostream>
#include "Pistol.h"
#include "Game.h"
#include "EntityManager.h"
#include "state_bullet.h"
#include "state_stop.h"

void Pistol::initialise()
{
	velocity = irr::core::vector3df(0.0f, 10.0f, 0.0f);
	alive = false;
	stateMachine.addState("Bullet", new Bullet());
	stateMachine.addState("Stop", new BulletStop());
	stateMachine.changeState("Stop");
}

void Pistol::loadContent()
{
	irr::scene::IAnimatedMesh* cube = game.getDevice()->getSceneManager()->getMesh("Media/Meshes/Cube.x");
	node = game.getDevice()->getSceneManager()->addAnimatedMeshSceneNode(cube);
	node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	node->setPosition(irr::core::vector3df(0.0f, 0.0f, 0.0f));
	node->setVisible(false);
	//std::cout<<"Pistol is alive!\n";
}

void Pistol::handleMessage(const Message& message)
{	
	
}
void Pistol::update(float deltaTime)
{
	stateMachine.update(deltaTime);
	
}
void Pistol::BulletState()
{
	stateMachine.changeState("Bullet");
}

void Pistol::StopState()
{
	stateMachine.changeState("Stop");
}
