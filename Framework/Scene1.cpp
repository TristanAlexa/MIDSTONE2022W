#include "Scene1.h"
#include "Player.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Timer.h"
#include "Debug.h"

Scene1::Scene1(SDL_Window* sdlWindow_){
	Debug::Info("Created Scene1: ", __FILE__, __LINE__);
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		printf("%s\n", SDL_GetError());
	}

	player = new Player(Vec3(5.0f, 5.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f), Vec3(0.0f, -9.8f, 0.0f), 5.0f);
	Timer::SetSingleEvent(5000, (void*)"Start");
}

Scene1::~Scene1(){
	delete player;
}

bool Scene1::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, 30.0f, 0.0f, 15.0f, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	//Turn on SDL Imaging subsystem
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface *playerImage = IMG_Load("textures/playerSprite.png");
	SDL_Texture* playerTexture = SDL_CreateTextureFromSurface(renderer, playerImage);
	if(playerImage == nullptr) {
		printf("cant open textures/playerSprite.png\n");
		return false;
	}
	player->setTexture(playerTexture);

	SDL_FreeSurface(playerImage);

	return true;
}

void Scene1::OnDestroy() {}

void Scene1::Update(const float deltaTime) {
	player->Update(deltaTime);

	//If player.pos collides with winnning game object end the scene
	// if (....) {game-aFunctionToSetABooleanToSwitchScene();} //will change a boolean in game manager
}

void Scene1::HandleEvents(const SDL_Event& sdlEvent) {
	if (sdlEvent.type == SDL_EventType::SDL_KEYDOWN) {
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_D) {
			player->ApplyForce(Vec3(100.0f, 0.0f, 0.0f));
			player->isMoving(true);
		}
	}
	else if (sdlEvent.type == SDL_EventType::SDL_KEYUP) {
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_D) {
			player->ApplyForce(Vec3(0.0f, 0.0f, 0.0f));
		}
	}
}
void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 112, 128, 144, 0); // drawing black
	SDL_RenderClear(renderer);

	SDL_Rect square;
	Vec3 screenCoords;
	int w, h;

	screenCoords = projectionMatrix * player->getPos();
	SDL_QueryTexture(player->getTexture(), nullptr, nullptr, &w, &h);
	square.x = static_cast<int>(screenCoords.x); 
	square.y = static_cast<int>(screenCoords.y);
	square.w = w/2;
	square.h = h/2;

	//Direction of movement = direction of sprite
	if (player->getVelocity().x >= 0.0f) {
		SDL_RenderCopyEx(renderer, player->getTexture(), nullptr, &square, 0.0, nullptr, SDL_FLIP_NONE);
	}
	else {
		SDL_RenderCopyEx(renderer, player->getTexture(), nullptr, &square, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
	}
	SDL_RenderPresent(renderer);
}