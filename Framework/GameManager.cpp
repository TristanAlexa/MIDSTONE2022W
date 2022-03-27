#include "GameManager.h"
#include "Window.h"
#include "Timer.h"
#include "Scene0.h"
#include "Scene1.h"
#include "Scene2.h"
#include "StartScene.h"
#include "EndScene.h"
#include <iostream>

GameManager::GameManager() {
	windowPtr = nullptr;
	timer = nullptr;
	isRunning = true;
	currentScene = nullptr;
	changeSceneEventType = false;
	//changeSceneEventType2 = false;
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

	// //Scene 2 not being created multiple times when changeSceneEvent type is initialized to false
	// //Gets created multiple times with the below *needed* line called. Therefore cannot register/create multiple events
	//changeSceneEventType = SDL_RegisterEvents(1); // create user defined events
	if (changeSceneEventType == ((Uint32) - 1) ) {
		OnDestroy();
		return false;
	}

	/*if (changeSceneEventType2 == ((Uint32)-1)) {
		OnDestroy();
		return false;
	}*/

	return true;
}

/// Here's the whole game
void GameManager::Run() {
	SDL_Event sdlEvent;
	timer->Start();
	while (isRunning) {
		while (SDL_PollEvent(&sdlEvent) != 0) {
			if (sdlEvent.type == SDL_EventType::SDL_QUIT) {
				isRunning = false;
			}
			else if (sdlEvent.type == SDL_EventType::SDL_KEYDOWN) {
				switch (sdlEvent.key.keysym.scancode) {
				case SDL_SCANCODE_ESCAPE:
					isRunning = false;
					break;

				case SDL_SCANCODE_Q:
					isRunning = false;
					break;

					// START GAME
				case SDL_SCANCODE_1:
					currentScene->OnDestroy();
					delete currentScene;
					currentScene = new Scene1(windowPtr->GetSDL_Window(), this);
					currentScene->OnCreate();
					break;
					
					// END SCREEN
				case SDL_SCANCODE_2:
					currentScene->OnDestroy();
					delete currentScene;
					currentScene = new EndScene(windowPtr->GetSDL_Window(), this);
					currentScene->OnCreate();
					break;

				//case SDL_SCANCODE_3:
				//	currentScene->OnDestroy();
				//	delete currentScene;
				//	currentScene = new Scene3(windowPtr->GetSDL_Window());
				//	currentScene->OnCreate();
				//	break;
				}
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
		}

		//else if (sdlEvent.type == changeSceneEventType2)
		//{
		//	// specific scene to scene switch
		//	currentScene->OnDestroy();
		//	delete currentScene;
		//	currentScene = new Scene0(windowPtr->GetSDL_Window(), this);
		//	if (!currentScene->OnCreate())
		//	{
		//		isRunning = false;
		//	}
		//}
			
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