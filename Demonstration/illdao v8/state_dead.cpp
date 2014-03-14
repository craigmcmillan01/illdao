#include "state_dead.h"
#include "Game.h"

using namespace irr::gui;


void Dead::execute(Player* owner, float frameTime)
{
	////----------set text------------------------ //setting text in a state
	//IGUIStaticText* text1;
	//irr::gui::IGUIEnvironment* guienv = game.getDevice()->getGUIEnvironment();
	//IGUIFont* font = guienv->getFont("Media/Textures/myfont.xml");
	////--------------------------------------------	
	//text1 = guienv->addStaticText(L"OMG YOU DEAD!", rect<s32>(500,310,1280,600),false);
	//text1->setText(L"YOU DEAD BITCH");
	//text1->setRelativePosition(rect<s32>(500,310,1280,600));
	//text1->setOverrideColor(video::SColor(255,255,255,255));
	//text1->setOverrideFont(font);		
		
	owner->getNode()->setFrameLoop(172, 172);
	owner->setdeathTime(game.getDevice()->getTimer()->getRealTime());//set time of death 
	owner->setAlive(false);//Kills player
	owner->setLives(owner->getLives() - 1);//remove a life

}