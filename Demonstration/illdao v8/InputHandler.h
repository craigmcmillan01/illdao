#pragma once

#include <irrlicht.h>

using namespace irr;
using namespace irr::core;

struct MouseState
{
	position2di Position;
	bool LeftButton;
	bool RightButton;
	bool MiddleButton;
};

class InputHandler : public irr::IEventReceiver
{
private:
	bool keyDown[irr::KEY_KEY_CODES_COUNT];
	bool prevKeyDown[irr::KEY_KEY_CODES_COUNT];
	MouseState CurrentMouse;
	MouseState PrevMouse;
public: 
	InputHandler()
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
		else if (event.EventType == EET_MOUSE_INPUT_EVENT)
		{
			switch (event.MouseInput.Event)
			{
			case EMIE_LMOUSE_PRESSED_DOWN:
				CurrentMouse.LeftButton = true;
				break;
			case EMIE_LMOUSE_LEFT_UP:
				CurrentMouse.LeftButton = false;
				break;
			case EMIE_RMOUSE_PRESSED_DOWN:
				CurrentMouse.RightButton = true;
				break;
			case EMIE_RMOUSE_LEFT_UP:
				CurrentMouse.RightButton = false;
				break;
			case EMIE_MOUSE_MOVED:
				CurrentMouse.Position.X = event.MouseInput.X;
				CurrentMouse.Position.Y = event.MouseInput.Y;
			}
		}
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
	MouseState getCurrentMouse() const
	{
		return CurrentMouse;
	}
	MouseState getPrevMouse() const
	{
		return PrevMouse;
	}
	void update()
	{
		std::memcpy(prevKeyDown, keyDown, sizeof(bool) * irr::KEY_KEY_CODES_COUNT);
		PrevMouse = CurrentMouse;
	}
};
