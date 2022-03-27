#include "StartScene.h"
#include "Player.h"
#include "Body.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Timer.h"
#include "Debug.h"
#include "VMath.h"
#include "CollisionManager.h"
#include "Scene.h"

StartScene::StartScene(SDL_Window* sdlWindow_, GameManager* game_) {

	//Render Start scene window
	Debug::Info("Created StartScene: ", __FILE__, __LINE__);
	window = sdlWindow_;
	game = game_;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		printf("%s\n", SDL_GetError());
	}

	spyTrainer = new Body(Vec3(-4.0f, 16.00f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	tristianGoode = new Body(Vec3(-4.0f, 13.00f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	nikkiLiu = new Body(Vec3(-4.0f, 11.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	davidValente = new Body(Vec3(-4.0f, 9.00f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	gameControls = new Body(Vec3(-4.0f, 6.00f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f);

	Timer::SetSingleEvent(5000, (void*)"Start");
}

StartScene::~StartScene() {
	delete spyTrainer;
	delete tristianGoode;
	delete nikkiLiu;
	delete davidValente;
	delete gameControls;
}

bool StartScene::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, 30.0f, 0.0f, 15.0f, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	//Turn on SDL Imaging subsystem and attach images to objects

	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* spyTrainerImage = IMG_Load("textures/SpyTrainer.png");
	SDL_Texture* spyTrainerTexture = SDL_CreateTextureFromSurface(renderer, spyTrainerImage);
	if (spyTrainerImage == nullptr) {
		printf("cant open textures/SpyTrainer.png\n");
		return false;
	}
	spyTrainer->setTexture(spyTrainerTexture);

	// get stone floor object dimensions
	textWidth = spyTrainer->getsize(spyTrainerTexture).x;
	textHeight = spyTrainer->getsize(spyTrainerTexture).y;
	printf("Floor Texture width: %d\n", textHeight);

	SDL_Surface* trisitanGoodeImage = IMG_Load("textures/TrisitanGoode.png");
	SDL_Texture* trisitanGoodeTexture = SDL_CreateTextureFromSurface(renderer, trisitanGoodeImage);
	if (trisitanGoodeImage == nullptr) {
		printf("cant open textures/Stone.jpg\n");
		return false;
	}
	tristianGoode->setTexture(trisitanGoodeTexture);

	SDL_Surface* nikkiLiuImage = IMG_Load("textures/NikkiLiu.png");
	SDL_Texture* nikkiLiuTexture = SDL_CreateTextureFromSurface(renderer, nikkiLiuImage);
	if (nikkiLiuImage == nullptr) {
		printf("cant open textures/NikkiLiu.png\n");
		return false;
	}
	nikkiLiu->setTexture(nikkiLiuTexture);

	SDL_Surface* davidValenteImage = IMG_Load("textures/DavidValente.png");
	SDL_Texture* davidValenteTexture = SDL_CreateTextureFromSurface(renderer, davidValenteImage);
	if (davidValenteImage == nullptr) {
		printf("cant open textures/DavidValente.png\n");
		return false;
	}
	davidValente->setTexture(davidValenteTexture);

	SDL_Surface* gameControlsImage = IMG_Load("textures/GameControls.png");
	SDL_Texture* gameControlsTexture = SDL_CreateTextureFromSurface(renderer, gameControlsImage);
	if (gameControlsImage == nullptr) {
		printf("cant open textures/GameControls.png\n");
		return false;
	}
	gameControls->setTexture(gameControlsTexture);

	SDL_FreeSurface(spyTrainerImage);
	SDL_FreeSurface(trisitanGoodeImage);
	SDL_FreeSurface(nikkiLiuImage);
	SDL_FreeSurface(davidValenteImage);
	SDL_FreeSurface(gameControlsImage);

	return true;
}

void StartScene::OnDestroy() {

}

void StartScene::Update(const float deltaTime) 
{
	// allow player to start game
	game->canEnterScene1 = true;
	
}

void StartScene::HandleEvents(const SDL_Event& sdlEvent) {

}

void StartScene::Render() {

	SDL_SetRenderDrawColor(renderer, 112, 128, 144, 0); // drawing grey colour for background
	SDL_RenderClear(renderer);

	SDL_Rect square;
	Vec3 screenCoords;
	int w, h;

	// Draw the title and names
	screenCoords = projectionMatrix * spyTrainer->getPos();
	SDL_QueryTexture(spyTrainer->getTexture(), nullptr, nullptr, &w, &h);
	square.x = static_cast<int>(screenCoords.x);
	square.y = static_cast<int>(screenCoords.y);
	square.w = w / 2;
	square.h = h / 3;
	SDL_RenderCopyEx(renderer, spyTrainer->getTexture(), nullptr, &square, 0.0, nullptr, SDL_FLIP_NONE);

	screenCoords = projectionMatrix * tristianGoode->getPos();
	SDL_QueryTexture(tristianGoode->getTexture(), nullptr, nullptr, &w, &h);
	square.x = static_cast<int>(screenCoords.x);
	square.y = static_cast<int>(screenCoords.y);
	square.w = w / 2;
	square.h = h / 3;
	SDL_RenderCopyEx(renderer, tristianGoode->getTexture(), nullptr, &square, 0.0, nullptr, SDL_FLIP_NONE);

	screenCoords = projectionMatrix * nikkiLiu->getPos();
	SDL_QueryTexture(nikkiLiu->getTexture(), nullptr, nullptr, &w, &h);
	square.x = static_cast<int>(screenCoords.x);
	square.y = static_cast<int>(screenCoords.y);
	square.w = w / 2;
	square.h = h / 3;
	SDL_RenderCopyEx(renderer, nikkiLiu->getTexture(), nullptr, &square, 0.0, nullptr, SDL_FLIP_NONE);

	screenCoords = projectionMatrix * davidValente->getPos();
	SDL_QueryTexture(davidValente->getTexture(), nullptr, nullptr, &w, &h);
	square.x = static_cast<int>(screenCoords.x);
	square.y = static_cast<int>(screenCoords.y);
	square.w = w / 2;
	square.h = h / 3;
	SDL_RenderCopyEx(renderer, davidValente->getTexture(), nullptr, &square, 0.0, nullptr, SDL_FLIP_NONE);

	screenCoords = projectionMatrix * gameControls->getPos();
	SDL_QueryTexture(gameControls->getTexture(), nullptr, nullptr, &w, &h);
	square.x = static_cast<int>(screenCoords.x);
	square.y = static_cast<int>(screenCoords.y);
	square.w = w / 2;
	square.h = h / 3;
	SDL_RenderCopyEx(renderer, gameControls->getTexture(), nullptr, &square, 0.0, nullptr, SDL_FLIP_NONE);

	SDL_RenderPresent(renderer);
}