#ifndef SCENE2_H
#define SCENE2_H

#include "MMath.h"
#include "Scene.h"
#include "GameManager.h"
#include <SDL.h>
#include <Vector>
#include "Body.h"
#include "Player.h"

using namespace MATH;
class Scene2 : public Scene
{
private:
	struct SDL_Window* window;
	struct SDL_Renderer* renderer;
	class Matrix4 projectionMatrix;
	class GameManager* game;

	class Player* player;
	class Body* progressionDoor;  // door to next scene

public:
	Scene2(SDL_Window* sdlWindow_, GameManager* game_);
	~Scene2();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& sdlEvent);
};

#endif

