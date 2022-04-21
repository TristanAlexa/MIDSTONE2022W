#ifndef STARTSCENE_H
#define STARTSCENE_H

#include "MMath.h"
#include "Scene.h"
#include "GameManager.h"
#include <SDL.h>
#include <Vector>
#include "Body.h"
#include "Player.h"

using namespace MATH;
class StartScene : public Scene {
private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	Matrix4 projectionMatrix;
	class GameManager *game;

	// title and names dimensions
	Body* spyTrainer, * tristianGoode, * nikkiLiu, * davidValente, * gameControls, *spy;
	int textWidth, textHeight;

public:
	StartScene(SDL_Window* sdlWindow_, GameManager* game_);
	~StartScene();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& sdlEvent);
};

#endif
