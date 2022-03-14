#include "GameManager.h"
#include "Window.h"
#include "Timer.h"
#include "Scene0.h"
#include "Scene1.h"
#include "Scene2.h"
#include <iostream>

GameManager::GameManager() {
	windowPtr = nullptr;
	timer = nullptr;
	isRunning = true;
	currentScene = nullptr;

	//create user defined events
	changeSceneEventType = SDL_RegisterEvents(1);
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

	if (changeSceneEventType == ((Uint32) - 1) ) {
		OnDestroy();
		return false;
	}

	return true;
}

/// Here's the whole game
void GameManager::Run() {
	SDL_Event sdlEvent;
	timer->Start();
	while (isRunning) {
		(SDL_PollEvent(&sdlEvent));
		
		if (sdlEvent.type == SDL_EventType::SDL_QUIT)
		{
			isRunning = false;
		}
		
		//Scene 2 constantly being created after event type is called
		else if (sdlEvent.type == changeSceneEventType)
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
		}
		//Check boolean for switching scenes/ending game if a certain value end the game/swtich scene
		timer->UpdateFrameTicks();
		currentScene->HandleEvents(sdlEvent);
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