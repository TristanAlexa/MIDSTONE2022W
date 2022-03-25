#ifndef SCENE3_H
#define SCENE3_H

#include "MMath.h"
#include "Scene.h"
#include "GameManager.h"
#include <SDL.h>
#include <Vector>
#include "Body.h"
#include "Player.h"
using namespace MATH;

class Scene3 : public Scene
{
	//Forward declarations
	struct SDL_Window* window;
	struct SDL_Renderer* renderer;
	Matrix4 projectionMatrix;
	GameManager* game; 

	class Player* player;

public:
	Scene3(SDL_Window* sdlWindow_, GameManager* game_);
	~Scene3();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& sdlEvent);
};

#endif;

