#pragma once

#include "Entity.h"
#include "Particle.h"
#include "Gravity.h"
#include "Drag.h"
#include "StateMachine.h"

using namespace irr;
using namespace irr::core;

class Player : public Entity
{
private:
	Particle particle;//set the properties need for the player
	Gravity gravity;
	Drag drag;
	vector3df velocity;
	StateMachine<Player> stateMachine;
	int Health;
	int MovementLeft;
	int ShotsLeft;
	irr::u32 deathTime;
	int livesleft;
	
public:
	Player(std::string num)
		: Entity(-1, 0, "Player" + num),
		particle(vector3df(0.0f, 0.0f, 0.0f), vector3df(0.0f, 0.0f, 0.0f), 1.0f),
		gravity(vector3df(0.0f, -10.0f, 0.0f)),
		drag(0.1f, 0.3f),
		stateMachine(this)
	{
	}
	~Player() { }

	//gets and sets
	irr::core::vector3df getVelocity() const { return velocity; }
	void setVelocity(irr::core::vector3df value) { velocity = value; }
	int getHealth() const { return Health; }
	void setHealth(int value) { Health = value; }
	int getMovementLeft() const { return MovementLeft; }
	void setMovementLeft(int value) { MovementLeft = value; }
	int getShotsLeft() const { return ShotsLeft; }
	void setShotsLeft(int value) { ShotsLeft = value; }
	int getLives() const { return livesleft; }
	void setLives(int value) { livesleft = value; }
	irr::u32 getdeathTime() const { return deathTime; }
	void setdeathTime(irr::u32 value) { deathTime = value; }
	Particle* getParticle() { return &particle; }

	//these methods are used to check which state the player is in. 
	State<Player>* getNormalState() { return stateMachine.getState("Normal"); }
	State<Player>* getShootingState() { return stateMachine.getState("Shooting"); }
	State<Player>* getMovementState() { return stateMachine.getState("Movement"); }
	State<Player>* getDieState() { return stateMachine.getState("Die"); }
	State<Player>* getReSpawnState() { return stateMachine.getState("Respawn"); }
	State<Player>* getCurrentState() { return stateMachine.getCurrentState(); }
	
	void initialise();
	void loadContent();
	void update(float deltaTime);
	void unloadContent() { }
	void handleMessage(const Message& message);
	void movementState();
	void shootingState();
	void normalState();
	void deadState();
	void ReSpawnState();	
};