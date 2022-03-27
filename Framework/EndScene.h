#ifndef ENDSCENE_H
#define ENDSCENE_H

#include "MMath.h"
#include "Scene.h"
#include "GameManager.h"
#include <SDL.h>
#include <Vector>
#include "Body.h"
#include "Player.h"

using namespace MATH;
class EndScene : public Scene {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Matrix4 projectionMatrix;
	class GameManager* game;

	// floor pointers and dimensions
	Body* spyTrainer, * gameOver, * endGameControls;
	int textWidth, textHeight;

public:
	EndScene(SDL_Window* sdlWindow_, GameManager* game_);
	~EndScene();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& sdlEvent);
};

#endif
