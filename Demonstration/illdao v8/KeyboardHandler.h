#pragma once

#include <irrlicht.h>

class KeyHandler : public irr::IEventReceiver
{
private:
	bool keyDown[irr::KEY_KEY_CODES_COUNT];
	bool prevKeyDown[irr::KEY_KEY_CODES_COUNT];
public:
	KeyHandler()
	{
		for(int i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
			keyDown[i] = false;
		for(int i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
			prevKeyDown[i] = false;
	}
	bool OnEvent(const irr::SEvent& event)
	{
		if(event.EventType == irr::EET_KEY_INPUT_EVENT)
			keyDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		return false;
	}
	bool isKeyDown(irr::EKEY_CODE key) const
	{
		return keyDown[key];
	}
	bool wasKeyDown(irr::EKEY_CODE key) const
	{
		return prevKeyDown[key];
	}
	void update()
	{
		std::memcpy(prevKeyDown, keyDown, sizeof(bool) * irr::KEY_KEY_CODES_COUNT);
	}
};