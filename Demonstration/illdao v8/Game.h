#pragma once

#include <string>
#include <irrlicht.h>
#include "KeyboardHandler.h"
#include "camera.h"
#include "camera_chase.h"
#include "InputHandler.h"

namespace GameEngine
{
	class Game
	{
	protected:
		irr::IrrlichtDevice* device;					// The underlying IrrlichtDevice used for rendering
		std::wstring caption;							// The Window Caption
		irr::core::dimension2d<irr::u32> dimensions;	// The Window Dimensions
		Camera* camera;									//the Camera for the game
		ChaseCamera* chaseCamera;						//chase camera
	public:
		Game() { }	// Creates a Game Class
		~Game() { }	// Destroys Game class
		irr::IrrlichtDevice* getDevice() { return device; }		// Gets underlying IrrlichtDevice
		std::wstring getCaption() const { return caption; }		// Gets the window caption
		void setCaption(const std::wstring& newCaption) { caption = newCaption; }		// Sets the window caption
		irr::core::dimension2d<irr::u32> getDimension() const { return dimensions; }		// Gets the screen dimensions
		void setDimension(const irr::core::dimension2d<irr::u32>& dim) { dimensions = dim; }		// Sets the screen dimensions

		//getters and setter for the camera
		Camera* getCamera() { return camera; }
		ChaseCamera* getChaseCam() { return chaseCamera; }
		void setCamera(Camera* value) { camera = value; }

		void initialise();				// Inititalises the Game
		void loadContent();				// Loads content associated with the game
		void update(float frameTime);	// The update stage of the game
		void render();					// The render stage of the game
		void unloadContent();			// Unloads any content assoiciated with the game
		void shutdown();				// Shuts down the game
	};
}

extern GameEngine::Game game;
extern KeyHandler keyHandler;
extern InputHandler handler;