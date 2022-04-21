#include "Scene1.h"
#include "Player.h"
#include "Body.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Timer.h"
#include "Debug.h"
#include "VMath.h"
#include "CollisionManager.h"

Scene1::Scene1(SDL_Window* sdlWindow_, GameManager* game_){

	//Render scene 1 window
	Debug::Info("Created Scene1: ", __FILE__, __LINE__);
	window = sdlWindow_;
	game = game_;

	renderer = SDL_GetRenderer(window);
	if (renderer == nullptr) {
		printf("%s\n", SDL_GetError());
	}

	//Create player object, set initial pos and health
	player = new Player();
	player->setPosition(Vec3(5.0f, 8.0f, 0.0f));
	player->setHealth(int (1));
	
	floor1 = new Body(Vec3(4.0f, 1.25f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	floor2 = new Body(Vec3(11.0f, 1.25f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	leftwall = new Body(Vec3(0.0f, 5.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	rightwall = new Body(Vec3(26.0f, 4.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	ceiling = new Body(Vec3(0.0f, 16.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	hidingspy = new Body(Vec3(0.0f, 7.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	progressionDoor = new Body();
	progressionDoor->setPos(Vec3(27.75f, 9.2f, 0.0f));
	Timer::SetSingleEvent(5000, (void*)"Start");
}

Scene1::~Scene1(){
	Debug::Info("Deleted Scene 1", __FILE__, __LINE__);
	delete player;
	delete floor1;
	delete floor2;
	delete leftwall;
	delete rightwall;
	delete ceiling;
	delete progressionDoor;
	delete hidingspy;
}

bool Scene1::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, 30.0f, 0.0f, 15.0f, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	//Turn on SDL Imaging subsystem and attach images to objects
	IMG_Init(IMG_INIT_PNG);

	//new player image
	SDL_Surface *playerImage = IMG_Load("textures/spygreycoatresized.png");
	SDL_Texture* playerTexture = SDL_CreateTextureFromSurface(renderer, playerImage);
	if(playerImage == nullptr) {
		printf("cant open textures/spygreycoatresized.png\n");
		return false;
	}
	player->setTexture(playerTexture);

	// get player texture dimensions
	playerWidth = player->getsize(playerTexture).x;
	printf("playerTexture width: %d\n", playerWidth); 
	playerHeight = player->getsize(playerTexture).y;
	printf("playerTexture height: %d\n", playerHeight);

	//add image to the door object
	IMG_Init(IMG_INIT_JPG);
	SDL_Surface* doorImage = IMG_Load("textures/door.jpg");
	SDL_Texture* doorTexture = SDL_CreateTextureFromSurface(renderer, doorImage);
	if (doorImage == nullptr) {
		printf("cant open textures/door.jpg\n");
		return false;
	}
	progressionDoor->setTexture(doorTexture);

	IMG_Init(IMG_INIT_JPG);
	SDL_Surface* floor1Image = IMG_Load("textures/Stone.jpg");
	SDL_Texture* floor1Texture = SDL_CreateTextureFromSurface(renderer, floor1Image);
	if (floor1Image == nullptr) {
		printf("cant open textures/Stone.jpg\n");
		return false;
	}
	floor1->setTexture(floor1Texture);

	// get stone floor object dimensions
	floorWidth = floor1->getsize(floor1Texture).x;
	floorHeight = floor1->getsize(floor1Texture).y;
	printf("Floor Texture width: %d\n", floorWidth);
	printf("Floor Texture height: %d\n", floorHeight);

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

	SDL_Surface* ceilingImage = IMG_Load("textures/Stone.jpg");
	SDL_Texture* ceilingTexture = SDL_CreateTextureFromSurface(renderer, ceilingImage);
	if (ceilingImage == nullptr) {
		printf("cant open textures/Stone.jpg\n");
		return false;
	}
	ceiling->setTexture(ceilingTexture);

	SDL_Surface* hidingspyImage = IMG_Load("textures/orangespyknife.jpg");
	SDL_Texture* hidingspyTexture = SDL_CreateTextureFromSurface(renderer, hidingspyImage);
	if (hidingspyImage == nullptr) {
		printf("cant open textures/Stone.jpg\n");
		return false;
	}
	hidingspy->setTexture(hidingspyTexture);

	SDL_FreeSurface(playerImage);
	SDL_FreeSurface(floor1Image);
	SDL_FreeSurface(floor2Image);
	SDL_FreeSurface(leftwallImage);
	SDL_FreeSurface(rightwallImage);
	SDL_FreeSurface(ceilingImage);
	SDL_FreeSurface(doorImage);
	SDL_FreeSurface(hidingspyImage);

	return true;
}

void Scene1::OnDestroy() {
	Debug::Info("Destroyed Scene 1", __FILE__, __LINE__);
}

void Scene1::Update(const float deltaTime) {
	player->Update(deltaTime);
	game->canEnterScene2 = false;
	game->canEnterEndScene = false;
	
	if (CollisionManager::checkCollision(player, floor1) == true)
	{
		// stop the player from updating its position
		//printf(" collision detected\n");
	}
	else if (CollisionManager::checkCollision(player, floor1) == false)
	{
		// move player normally
		//printf("No collision detected\n");
	}

	//if (CollisionManager::checkCollision(player, damageDealer) == true)
	//{
	//	// instantly kill the player
	//	player->TakeDamage(1)
	//}
	
	
	// Push change scene event to queue when player reaches right side of screen
	Vec3 bottomRight(27.0f, 8.0f, 0.0f);
	if (VMath::distance(player->getPos(), bottomRight) < 1.5f)
	{
		// set can switch scenes to true
		game->canEnterScene2 = true;
	}

	// if player is dead call end scene
	if (player->isDead())
	{
		game->canEnterEndScene = true;
		//create event for automatic scene switch
		SDL_Event event;
		SDL_memset(&event, 0, sizeof(event));
		event.type = game->getGameOverEvent();
		event.user.code = 1;
		event.user.data1 = nullptr;
		event.user.data2 = nullptr;
		SDL_PushEvent(&event);
	}
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
}

void Scene1::Render() {
	
	SDL_SetRenderDrawColor(renderer, 112, 128, 144, 0); // drawing grey colour for background
	SDL_RenderClear(renderer);

	SDL_Rect square;
	Vec3 screenCoords;
	int w, h;

	// Draw the stone floor, left, right wall & ceiling
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
	square.w = w * 1.2;
	square.h = h / 3;
	SDL_RenderCopyEx(renderer, floor2->getTexture(), nullptr, &square, 0.0, nullptr, SDL_FLIP_NONE);

	screenCoords = projectionMatrix * leftwall->getPos();
	SDL_QueryTexture(leftwall->getTexture(), nullptr, nullptr, &w, &h);
	square.x = static_cast<int>(screenCoords.x);
	square.y = static_cast<int>(screenCoords.y);
	square.w = w / 3;
	square.h = h / 1.2;
	SDL_RenderCopyEx(renderer, leftwall->getTexture(), nullptr, &square, 0.0, nullptr, SDL_FLIP_NONE);

	screenCoords = projectionMatrix * rightwall->getPos();
	SDL_QueryTexture(rightwall->getTexture(), nullptr, nullptr, &w, &h);
	square.x = static_cast<int>(screenCoords.x);
	square.y = static_cast<int>(screenCoords.y);
	square.w = w / 3;
	square.h = h / 1.5;
	SDL_RenderCopyEx(renderer, rightwall->getTexture(), nullptr, &square, 0.0, nullptr, SDL_FLIP_NONE);

	//Draw the ceiling and modify its size
	screenCoords = projectionMatrix * ceiling->getPos();
	SDL_QueryTexture(ceiling->getTexture(), nullptr, nullptr, &w, &h);
	square.x = static_cast<int>(screenCoords.x);
	square.y = static_cast<int>(screenCoords.y);
	square.w = w * 2.2;
	square.h = h / 3;
	SDL_RenderCopyEx(renderer, ceiling->getTexture(), nullptr, &square, 0.0, nullptr, SDL_FLIP_NONE);

	//Draw the door and modify its size
	screenCoords = projectionMatrix * progressionDoor->getPos();
	SDL_QueryTexture(progressionDoor->getTexture(), nullptr, nullptr, &w, &h);
	square.x = static_cast<int>(screenCoords.x);
	square.y = static_cast<int>(screenCoords.y);
	square.w = w;
	square.h = h;
	SDL_RenderCopyEx(renderer, progressionDoor->getTexture(), nullptr, &square, 0.0, nullptr, SDL_FLIP_NONE);

	screenCoords = projectionMatrix * hidingspy->getPos();
	SDL_QueryTexture(hidingspy->getTexture(), nullptr, nullptr, &w, &h);
	square.x = static_cast<int>(screenCoords.x);
	square.y = static_cast<int>(screenCoords.y);
	square.w = w / 3.6;
	square.h = h / 3;
	SDL_RenderCopyEx(renderer, hidingspy->getTexture(), nullptr, &square, 0.0, nullptr, SDL_FLIP_NONE);

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