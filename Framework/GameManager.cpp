#include "GameManager.h"
#include "Window.h"
#include "Timer.h"
#include "Scene0.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include <iostream>

GameManager::GameManager() {
	windowPtr = nullptr;
	timer = nullptr;
	isRunning = true;
	currentScene = nullptr;
	canEnterScene2 = false;
	canEnterScene3 = false;
}

/// In this OnCreate() method, fuction, subroutine, whatever the word, 
bool GameManager::OnCreate() {
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;
	windowPtr = new Window(SCREEN_WIDTH, SCREEN_HEIGHT);

	if (windowPtr == nullptr) {
		OnDestroy();
		return false;
	}
	if (windowPtr->OnCreate() == false) {
		OnDestroy();
		return false;
	}

	timer = new Timer();
	if (timer == nullptr) {
		OnDestroy();
		return false;
	}

	currentScene = new Scene1(windowPtr->GetSDL_Window(), this);
	if (currentScene == nullptr) {
		OnDestroy();
		return false;
	}

	if (currentScene->OnCreate() == false) {
		OnDestroy();
		return false;
	}

	return true;
}

/// Here's the whole game
void GameManager::Run() {
	
	timer->Start();
	while (isRunning) {

		SDL_Event sdlEvent;
		SDL_PumpEvents();

		while (SDL_PollEvent(&sdlEvent)) 
		{
			if (sdlEvent.type == SDL_EventType::SDL_QUIT)
			{
				isRunning = false;
			}

			else if (sdlEvent.type == SDL_EventType::SDL_KEYDOWN)
			{
				if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					isRunning = false;
				}
				else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_Q)
				{
					isRunning = false;
				}
				// switch scene on button press
				else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_E)
				{
					if (canEnterScene2 && !canEnterScene3)
					{
						// specific scene to scene switch
						currentScene->OnDestroy();
						delete currentScene;
						currentScene = new Scene2(windowPtr->GetSDL_Window(), this);
						if (!currentScene->OnCreate())
						{
							isRunning = false;
						}
					}
					else if (canEnterScene3 && !canEnterScene2)
					{
						currentScene->OnDestroy();
						delete currentScene;
						currentScene = new Scene3(windowPtr->GetSDL_Window(), this);
						if (!currentScene->OnCreate())
						{
							isRunning = false;
						}
					}
				}
			}
			currentScene->HandleEvents(sdlEvent);
		}

		//Check boolean for switching scenes/ending game if a certain value end the game/swtich scene
		timer->UpdateFrameTicks();
		currentScene->Update(timer->GetDeltaTime());
		currentScene->Render();
		/// Keeep the event loop running at a proper rate
		SDL_Delay(timer->GetSleepTime(60)); ///60 frames per sec
	}
}

GameManager::~GameManager() {}

void GameManager::OnDestroy(){
	if (windowPtr) delete windowPtr;
	if (timer) delete timer;
	if (currentScene) delete currentScene;
}