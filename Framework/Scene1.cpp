#include "Scene1.h"
#include "Player.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Timer.h"
#include "Debug.h"


//Current problems: //After pressing A key and moving left, player sprite resets to face right.
					//Player can jump an infinite amount of times (add isGrounded boolean)
					//Need correct floor and roof collisions so player does not bounce. (TRELLO CARD: FRAME LEVEL PATH WITH COLLISION BOXES)
Scene1::Scene1(SDL_Window* sdlWindow_){

	//Render scene 1 window
	Debug::Info("Created Scene1: ", __FILE__, __LINE__);
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		printf("%s\n", SDL_GetError());
	}

	//Create player object with initial pos vel and accel vec
	player = new Player();
	player->setPosition(Vec3(1.0f, 5.0f, 0.0f));
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

	//Turn on SDL Imaging subsystem and attach images to objects
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
	
	//Gails code optional way of player and game manager communication can do if we want
	//If player.pos collides with winnning game object end the scene
	// if (....) {game-aFunctionToSetABooleanToSwitchScene();} //will change a boolean in game manager
}

void Scene1::HandleEvents(const SDL_Event& sdlEvent) {
	//Handle player movement events
	if (sdlEvent.type == SDL_EventType::SDL_KEYDOWN) {
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_D) {
			player->ApplyForceX(5.0f);
			player->isMoving(true);
		}
	}
	else if (sdlEvent.type == SDL_EventType::SDL_KEYUP) {
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_D) {
			player->UnsetForceX();
			player->setVelocity(Vec3(0.0f, 0.0f, 0.0f));
			player->isMoving(false);
		}
	}

	if (sdlEvent.type == SDL_EventType::SDL_KEYDOWN) {
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_A) {
			player->ApplyForceX(-5.0f);
			player->isMoving(true);
		}
	}
	else if (sdlEvent.type == SDL_EventType::SDL_KEYUP) {
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_A) {
			player->UnsetForceX();
			player->isMoving(false);
		}
	}

	if (sdlEvent.type == SDL_EventType::SDL_KEYDOWN) {
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_SPACE) {
			Debug::Info("Spacebar is pressed!", __FILE__, __LINE__);
			player->ApplyForceY(100.0f);
			player->isMoving(true);
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
}