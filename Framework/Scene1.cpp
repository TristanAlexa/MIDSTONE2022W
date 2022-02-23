#include "Scene1.h"
#include "Player.h"
#include "Body.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Timer.h"
#include "Debug.h"
#include "VMath.h"

Scene1::Scene1(SDL_Window* sdlWindow_){

	//Render scene 1 window
	Debug::Info("Created Scene1: ", __FILE__, __LINE__);
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		printf("%s\n", SDL_GetError());
	}

	//Create player object, set initial pos
	player = new Player();
	player->setPosition(Vec3(5.0f, 5.0f, 0.0f));

	floor1 = new Body(Vec3(4.0f, 1.25f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	floor2 = new Body(Vec3(15.0f, 1.25f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	leftwall = new Body(Vec3(0.0f, 7.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	rightwall = new Body(Vec3(26.0f, 4.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f);

	Timer::SetSingleEvent(5000, (void*)"Start");
}

Scene1::~Scene1(){
	delete player;
	delete floor1;
	delete floor2;
	delete leftwall;
	delete rightwall;
}

bool Scene1::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, 30.0f, 0.0f, 15.0f, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	//Turn on SDL Imaging subsystem and attach images to objects
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface *playerImage = IMG_Load("textures/playerSprite.png");
	SDL_Texture* playerTexture = SDL_CreateTextureFromSurface(renderer, playerImage);
	if(playerImage == nullptr) {
		printf("cant open textures/playerSprite.png\n");
		return false;
	}
	player->setTexture(playerTexture);

	IMG_Init(IMG_INIT_JPG);
	SDL_Surface* floor1Image = IMG_Load("textures/Stone.jpg");
	SDL_Texture* floor1Texture = SDL_CreateTextureFromSurface(renderer, floor1Image);
	if (floor1Image == nullptr) {
		printf("cant open textures/Stone.jpg\n");
		return false;
	}
	floor1->setTexture(floor1Texture);

	SDL_Surface* floor2Image = IMG_Load("textures/Stone.jpg");
	SDL_Texture* floor2Texture = SDL_CreateTextureFromSurface(renderer, floor2Image);
	if (floor1Image == nullptr) {
		printf("cant open textures/Stone.jpg\n");
		return false;
	}
	floor2->setTexture(floor2Texture);

	SDL_Surface* leftwallImage = IMG_Load("textures/Stone.jpg");
	SDL_Texture* leftwallTexture = SDL_CreateTextureFromSurface(renderer, leftwallImage);
	if (leftwallImage == nullptr) {
		printf("cant open textures/Stone.jpg\n");
		return false;
	}
	leftwall->setTexture(leftwallTexture);

	SDL_Surface* rightwallImage = IMG_Load("textures/Stone.jpg");
	SDL_Texture* rightwallTexture = SDL_CreateTextureFromSurface(renderer, rightwallImage);
	if (rightwallImage == nullptr) {
		printf("cant open textures/Stone.jpg\n");
		return false;
	}
	rightwall->setTexture(rightwallTexture);

	SDL_FreeSurface(playerImage);
	SDL_FreeSurface(floor1Image);
	SDL_FreeSurface(floor2Image);
	SDL_FreeSurface(leftwallImage);
	SDL_FreeSurface(rightwallImage);

	return true;
}

void Scene1::OnDestroy() {}

void Scene1::Update(const float deltaTime) {
	player->Update(deltaTime);
	
	//Gails code optional way of player and game manager communication can do if we want
	//If player.pos collides with winnning game object end the scene
	// if (....) {game-aFunctionToSetABooleanToSwitchScene();} //will change a boolean in game manager
}

void Scene1::HandleEvents(const SDL_Event& sdlEvent) {
	//Handle player movement events
	if (sdlEvent.type == SDL_EventType::SDL_KEYDOWN) {
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_D) {
			player->setVelocityX(5.0f);
		}
	}
	else if (sdlEvent.type == SDL_EventType::SDL_KEYUP) {
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_D && player->isGrounded()) {
			//only set vel to 0 if player is grounded
			player->setVelocityX(0.0f);
		}
	}

	if (sdlEvent.type == SDL_EventType::SDL_KEYDOWN) {
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_A) {
			player->setVelocityX(-5.0f);
		}
	}
	else if (sdlEvent.type == SDL_EventType::SDL_KEYUP) {
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_A && player->isGrounded()) {
			//only set vel to 0 if player isgrounded
			player->setVelocityX(0.0f);
		}
	}

	if (sdlEvent.type == SDL_EventType::SDL_KEYDOWN) {
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_SPACE && player->isGrounded()) {
			//only allow player to jump if they were grounded
			player->setVelocityY(10.0f);
		}
	}

	else if (sdlEvent.type == SDL_EventType::SDL_KEYUP) {
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_SPACE) {
			player->UnsetForceY();
		}
	}
}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 112, 128, 144, 0); // drawing grey colour for background
	SDL_RenderClear(renderer);

	SDL_Rect square;
	Vec3 screenCoords;
	int w, h;

	// Draw the stone floor, left & right wall
	screenCoords = projectionMatrix * floor1->getPos();
	SDL_QueryTexture(floor1->getTexture(), nullptr, nullptr, &w, &h);
	square.x = static_cast<int>(screenCoords.x);
	square.y = static_cast<int>(screenCoords.y);
	square.w = w / 2;
	square.h = h / 3;
	SDL_RenderCopyEx(renderer, floor1->getTexture(), nullptr, &square, 0.0, nullptr, SDL_FLIP_NONE);

	screenCoords = projectionMatrix * floor2->getPos();
	SDL_QueryTexture(floor2->getTexture(), nullptr, nullptr, &w, &h);
	square.x = static_cast<int>(screenCoords.x);
	square.y = static_cast<int>(screenCoords.y);
	square.w = w /2;
	square.h = h / 3;
	SDL_RenderCopyEx(renderer, floor2->getTexture(), nullptr, &square, 0.0, nullptr, SDL_FLIP_NONE);

	screenCoords = projectionMatrix * leftwall->getPos();
	SDL_QueryTexture(leftwall->getTexture(), nullptr, nullptr, &w, &h);
	square.x = static_cast<int>(screenCoords.x);
	square.y = static_cast<int>(screenCoords.y);
	square.w = w / 3;
	square.h = h * 2;
	SDL_RenderCopyEx(renderer, leftwall->getTexture(), nullptr, &square, 0.0, nullptr, SDL_FLIP_NONE);

	screenCoords = projectionMatrix * rightwall->getPos();
	SDL_QueryTexture(rightwall->getTexture(), nullptr, nullptr, &w, &h);
	square.x = static_cast<int>(screenCoords.x);
	square.y = static_cast<int>(screenCoords.y);
	square.w = w / 3;
	square.h = h / 1.5;
	SDL_RenderCopyEx(renderer, rightwall->getTexture(), nullptr, &square, 0.0, nullptr, SDL_FLIP_NONE);

	//Draw the player in its given position and modify its size
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

	// SDL_UpdateWindowSurface(window);
}