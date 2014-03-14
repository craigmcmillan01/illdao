#include "Map.h"
#include "Game.h"
#include <iostream>
#include "EntityManager.h"
#include "Player.h"
#include"Pistol.h"

using namespace irr::core;

void Map::initialise() { }

void Map::loadContent()
{
	Player* player_1 = (Player*)EntityManager::getNamedEntities("Player1")->front(); 
	Player* player_2 = (Player*)EntityManager::getNamedEntities("Player2")->front();
	Player* player_3 = (Player*)EntityManager::getNamedEntities("Player3")->front();
	Player* player_4 = (Player*)EntityManager::getNamedEntities("Player4")->front();
	//------------------------------------------------map-------------------------------------------------------------
	scene::IAnimatedMesh* mapMesh = game.getDevice()->getSceneManager()->getMesh("Media/Meshes/map.3ds");
	scene::IMeshSceneNode* mapNode = 0;
	scene::ITriangleSelector* selector = 0;

	if (mapMesh)
	{
		game.getDevice()->getSceneManager()->getMeshManipulator()->makePlanarTextureMapping(mapMesh->getMesh(0));
		video::ITexture* normalMap = game.getDevice()->getVideoDriver()->getTexture("Media/Textures/map.jpg");
		if (normalMap)	game.getDevice()->getVideoDriver()->makeNormalMapTexture(normalMap, 8.0f);
		
		scene::IMesh* tangentMesh = game.getDevice()->getSceneManager()->getMeshManipulator()->createMeshWithTangents(mapMesh->getMesh(0));
		mapNode = game.getDevice()->getSceneManager()->addMeshSceneNode(tangentMesh);
		mapNode->setMaterialTexture(1, normalMap);
		mapNode->getMaterial(0).SpecularColor.set(0, 0, 0, 0);
		mapNode->setMaterialType(video::EMT_PARALLAX_MAP_SOLID);

		mapNode->getMaterial(0).MaterialTypeParam = 0.035f;		// adjust height for parallax effect

		if(mapNode)
		{
		mapNode->setRotation(vector3df(0.0f,0.0f,0.0f));
		mapNode->setScale(vector3df(0.05f,0.05f,0.05f));
		mapNode->setPosition(vector3df(-80,0,-100));		
		
		selector = game.getDevice()->getSceneManager()->createOctreeTriangleSelector(mapNode->getMesh(), mapNode, 128);
		mapNode->setTriangleSelector(selector);
		}
		tangentMesh->drop();
	}	
			
	vector3df ellip = vector3df(3,1,3);
	vector3df grav = vector3df(0,-10,0);
	vector3df trans = vector3df(0,-1,0);
	if (selector)
	{
		//allow collision with player 1
		scene::ISceneNodeAnimator* p1Anim = game.getDevice()->getSceneManager()->createCollisionResponseAnimator(selector, player_1->getNode(), ellip, grav, trans);
		player_1->getNode()->addAnimator(p1Anim);
		p1Anim->drop();
		
		//allow collision with player 2
		p1Anim = game.getDevice()->getSceneManager()->createCollisionResponseAnimator(selector, player_2->getNode(), ellip,	grav, trans);
		player_2->getNode()->addAnimator(p1Anim);
		p1Anim->drop();
		
		//allow collision with player 3
		p1Anim = game.getDevice()->getSceneManager()->createCollisionResponseAnimator(selector, player_3->getNode(), ellip,grav, trans);
		player_3->getNode()->addAnimator(p1Anim);
		p1Anim->drop();
		
		//allow collision with player 4
		p1Anim = game.getDevice()->getSceneManager()->createCollisionResponseAnimator(selector, player_4->getNode(), ellip, grav, trans);
		player_4->getNode()->addAnimator(p1Anim);
		p1Anim->drop();
		//allow collision with bullets
		std::list<Entity*>* entities = EntityManager::getNamedEntities("Pistol");
		std::list<Entity*>::iterator pistol = entities->begin();
		for (; pistol != entities->end(); ++pistol)
		{
		p1Anim = game.getDevice()->getSceneManager()->createCollisionResponseAnimator(
		selector, (*pistol)[0].getNode(), vector3df(1,1,1), vector3df(0,0,0), vector3df(0,0,0));
		(*pistol)[0].getNode()->addAnimator(p1Anim);
		p1Anim->drop();
		break;
		}
		selector->drop();
	}	
}

void Map::update(float deltaTime) { }

