#pragma once 

#include "Entity.h"

using namespace std;
using namespace irr::core;

class Map : public Entity
{
private:
	
	
public:
	Map()
		: Entity(-1, 0, "Map")
	{
	}
	~Map() { }
	void initialise();
	void loadContent();
	void update(float deltaTime);
	void unloadContent() { }
};