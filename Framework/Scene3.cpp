#include "Scene3.h"
#include "Player.h"
#include "Body.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Timer.h"
#include "Debug.h"
#include "VMath.h"

Scene3::Scene3(SDL_Window* sdlWindow_, GameManager* game_)
{
	Debug::Info("Created Scene3: ", __FILE__, __LINE__);
	window = sdlWindow_;
	game = game_;

	// Render scene 3 window
	renderer = SDL_GetRenderer(window);
	if (renderer == nullptr) {
		printf("%s\n", SDL_GetError());
	}

	//Create player object, set initial pos
	player = new Player();
	player->setPosition(Vec3(3.0f, 5.0f, 0.0f));

	Timer::SetSingleEvent(5000, (void*)"Start");
}

Scene3::~Scene3()
{
	delete player;
}

bool Scene3::OnCreate()
{
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, 30.0f, 0.0f, 15.0f, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	//Turn on SDL Imaging subsystem and attach images to objects
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* playerImage = IMG_Load("textures/playerSprite.png");
	SDL_Texture* playerTexture = SDL_CreateTextureFromSurface(renderer, playerImage);
	if (playerImage == nullptr) {
		printf("cant open textures/playerSprite.png\n");
		return false;
	}
	player->setTexture(playerTexture);
	SDL_FreeSurface(playerImage);

	return true;
}

void Scene3::OnDestroy()
{
}

void Scene3::Update(const float deltaTime)
{
	player->Update(deltaTime);

	// set other scene switch booleans to false;
	game->canEnterScene2 = false;
	game->canEnterScene3 = false;

	// Checking when to change scene
	Vec3 bottomRight(27.0f, 6.0f, 0.0f);
	if (VMath::distance(player->getPos(), bottomRight) < 1.5f)
	{
		//game->canEnterScene4 = true;
	}
}

void Scene3::HandleEvents(const SDL_Event& sdlEvent)
{
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


void Scene3::Render()
{

	SDL_SetRenderDrawColor(renderer, 200, 100, 100, 0); // red colour to know we are in scene 3
	SDL_RenderClear(renderer);

	SDL_Rect square;
	Vec3 screenCoords;
	int w, h;

	//Draw the player in its given position and modify its size
	screenCoords = projectionMatrix * player->getPos();
	SDL_QueryTexture(player->getTexture(), nullptr, nullptr, &w, &h);
	square.x = static_cast<int>(screenCoords.x);
	square.y = static_cast<int>(screenCoords.y);
	square.w = w / 2;
	square.h = h / 2;

	//Direction of movement = direction of sprite
	if (player->getVelocity().x >= 0.0f) {
		SDL_RenderCopyEx(renderer, player->getTexture(), nullptr, &square, 0.0, nullptr, SDL_FLIP_NONE);
	}
	else {
		SDL_RenderCopyEx(renderer, player->getTexture(), nullptr, &square, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
	}
	SDL_RenderPresent(renderer);
}
