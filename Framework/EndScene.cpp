#include "EndScene.h"
#include "Player.h"
#include "Body.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Timer.h"
#include "Debug.h"
#include "VMath.h"
#include "CollisionManager.h"
#include "Scene.h"

EndScene::EndScene(SDL_Window* sdlWindow_, GameManager* game_) {

	//Render end scene window
	Debug::Info("Created EndScene: ", __FILE__, __LINE__);
	window = sdlWindow_;
	game = game_;

	renderer = SDL_GetRenderer(window);
	if (renderer == nullptr) {
		printf("%s\n", SDL_GetError());
	}

	spyTrainer = new Body(Vec3(-4.0f, 16.00f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	gameOver = new Body(Vec3(-4.0f, 11.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	endGameControls = new Body(Vec3(-4.0f, 6.00f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f);

	Timer::SetSingleEvent(5000, (void*)"Start");
}

EndScene::~EndScene() {
	delete spyTrainer;
	delete gameOver;
	delete endGameControls;
}

bool EndScene::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, 30.0f, 0.0f, 15.0f, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	//Turn on SDL Imaging subsystem and attach images to objects
	IMG_Init(IMG_INIT_PNG);

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

	SDL_Surface* gameOverImage = IMG_Load("textures/GameOver.png");
	SDL_Texture* gameOverTexture = SDL_CreateTextureFromSurface(renderer, gameOverImage);
	if (gameOverImage == nullptr) {
		printf("cant open textures/Stone.jpg\n");
		return false;
	}
	gameOver->setTexture(gameOverTexture);

	SDL_Surface* endGameControlsImage = IMG_Load("textures/EndGameControls.png");
	SDL_Texture* endGameControlsTexture = SDL_CreateTextureFromSurface(renderer, endGameControlsImage);
	if (endGameControlsImage == nullptr) {
		printf("cant open textures/NikkiLiu.png\n");
		return false;
	}
	endGameControls->setTexture(endGameControlsTexture);

	SDL_FreeSurface(spyTrainerImage);
	SDL_FreeSurface(gameOverImage);
	SDL_FreeSurface(endGameControlsImage);

	return true;
}

void EndScene::OnDestroy() {

}

void EndScene::Update(const float deltaTime) {
	// stop's multiple creations of end scene from automatic scene switch
	game->canEnterEndScene = false;
}

void EndScene::HandleEvents(const SDL_Event& sdlEvent) {

}

void EndScene::Render() {

	SDL_SetRenderDrawColor(renderer, 112, 128, 144, 0); // drawing grey colour for background
	SDL_RenderClear(renderer);

	SDL_Rect square;
	Vec3 screenCoords;
	int w, h;

	// Draw the stone floor, left & right wall
	screenCoords = projectionMatrix * spyTrainer->getPos();
	SDL_QueryTexture(spyTrainer->getTexture(), nullptr, nullptr, &w, &h);
	square.x = static_cast<int>(screenCoords.x);
	square.y = static_cast<int>(screenCoords.y);
	square.w = w / 2;
	square.h = h / 3;
	SDL_RenderCopyEx(renderer, spyTrainer->getTexture(), nullptr, &square, 0.0, nullptr, SDL_FLIP_NONE);

	screenCoords = projectionMatrix * gameOver->getPos();
	SDL_QueryTexture(gameOver->getTexture(), nullptr, nullptr, &w, &h);
	square.x = static_cast<int>(screenCoords.x);
	square.y = static_cast<int>(screenCoords.y);
	square.w = w / 2;
	square.h = h / 3;
	SDL_RenderCopyEx(renderer, gameOver->getTexture(), nullptr, &square, 0.0, nullptr, SDL_FLIP_NONE);

	screenCoords = projectionMatrix * endGameControls->getPos();
	SDL_QueryTexture(endGameControls->getTexture(), nullptr, nullptr, &w, &h);
	square.x = static_cast<int>(screenCoords.x);
	square.y = static_cast<int>(screenCoords.y);
	square.w = w / 2;
	square.h = h / 3;
	SDL_RenderCopyEx(renderer, endGameControls->getTexture(), nullptr, &square, 0.0, nullptr, SDL_FLIP_NONE);

	SDL_RenderPresent(renderer);
}