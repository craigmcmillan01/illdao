#include <iostream>
#include "Player.h"
#include "Game.h"
#include "EntityManager.h"
#include "MessageHandler.h"
#include "state_movement.h"
#include "state_shooting.h"
#include "state_normal.h"
#include "state_spawn.h"
#include "state_dead.h"
#include "state_respawn.h"

using namespace irr;
using namespace irr::core;

void Player::initialise()
{
	velocity = vector3df(10.0f, 0.0f, 0.0f);	
	stateMachine.addState("Movement", new Movement());//add in movement and shooting states
	stateMachine.addState("Normal", new Normal());
	stateMachine.addState("Spawn", new SpawnState());
	stateMachine.addState("Die", new Dead());
	stateMachine.addState("ReSpawn", new ReSpawn());
	stateMachine.changeState("Spawn");//set initial state as spawn
}

void Player::loadContent()
{
	scene::IAnimatedMesh* player = game.getDevice()->getSceneManager()->getMesh("Media/Meshes/ninja.b3d");//set mesh
	node = game.getDevice()->getSceneManager()->addAnimatedMeshSceneNode(player, 0);

	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setPosition(vector3df(-10.0f,0.0f,0.0f));
	node->setScale(vector3df(1.0f,1.0f,1.0f));
	node->setMaterialTexture( 0, game.getDevice()->getVideoDriver()->getTexture("Media/Textures/nskinbb.jpg") );//set texture
	node->setMaterialType( video::EMT_SOLID );
}
void Player::handleMessage(const Message& message) { }

//main player update 
void Player::update(float deltaTime) { stateMachine.update(deltaTime); }

//these methods allow the player to be switched to different states
void Player::movementState()	{ stateMachine.changeState("Movement"); }
void Player::shootingState()	{ stateMachine.changeState("Shooting"); }
void Player::normalState()		{ stateMachine.changeState("Normal");	}
void Player::deadState()		{ stateMachine.changeState("Die");		}
void Player::ReSpawnState()		{ stateMachine.changeState("ReSpawn");	}