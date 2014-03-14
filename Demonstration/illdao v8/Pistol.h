#pragma once

#include "Entity.h"
#include "Particle.h"
#include "StateMachine.h"

class Pistol : public Entity
{
private:
	irr::core::vector3df velocity; 
	Particle particle;
	StateMachine<Pistol> stateMachine;
public:
	Pistol() : Entity(-1, 0, "Pistol"),
	particle(vector3df(0.0f, 0.0f, 0.0f), vector3df(0.0f, 0.0f, 0.0f), 1.0f),
	stateMachine(this){ }
	Pistol(irr::scene::IAnimatedMeshSceneNode* node) : Entity(-1, node, "Pistol"),
	particle(vector3df(0.0f, 0.0f, 0.0f), vector3df(0.0f, 0.0f, 0.0f), 1.0f),
	stateMachine(this){ }
	~Pistol() { }
	irr::core::vector3df getVelocity() const { return velocity; } 
	void setVelocity(irr::core::vector3df value) { velocity = value; }
	Particle* getParticle() { return &particle; }
	void initialise();
	void loadContent();
	void update(float deltaTime);
	void unloadContent() { }
	void handleMessage (const Message& message);
	void StopState();
	void BulletState();
};