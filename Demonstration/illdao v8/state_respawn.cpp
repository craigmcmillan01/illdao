#include "state_respawn.h"
#include "Game.h"
#include <iostream>

void ReSpawn::execute(Player* owner, float frameTime)
{
 owner->getNode()->setFrameLoop(212,227);
 owner->setAlive(true);
 owner->getNode()->setVisible(true);
 owner->setHealth(10);
 std::cout<<"Player " <<owner->getID() + 1<<" has respawned!\n";
}