#pragma once

#include <irrlicht.h>
#include "Message.h"

class Entity
{
protected:
	int id;
	std::string name;
	//irr::scene::ISceneNode* node;
	irr::scene::IAnimatedMeshSceneNode* node;
	bool alive;
public:
	Entity(int id,irr::scene::IAnimatedMeshSceneNode* node, std::string name = "") ;
	virtual ~Entity();
	irr::scene::IAnimatedMeshSceneNode* getNode() { return node; }
	void setNode(irr::scene::IAnimatedMeshSceneNode* node) {node = node;}//added this in
	int getID() const { return id; }
	void setID( int value) { id = value; }
	std::string getName() const { return name; }
	void setName(const std::string& value) { name = value; }
	bool isAlive() const { return alive; }
	void setAlive(bool value) { alive = value; }
	virtual void initialise() = 0;
	virtual void loadContent() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void unloadContent() = 0;
	virtual void handleMessage(const Message& message) { }
};