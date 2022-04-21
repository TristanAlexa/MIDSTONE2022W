#ifndef SCENE1_H
#define SCENE1_H

#include "MMath.h"
#include "Scene.h"
#include "GameManager.h"
#include <SDL.h>
#include <Vector>
#include "Body.h"
#include "Player.h"

using namespace MATH;
class Scene1 : public Scene {
private:
	struct SDL_Window *window;
	struct SDL_Renderer *renderer;
	Matrix4 projectionMatrix;
	Matrix4 invProjectionMatrix;
	class GameManager* game;
	//Body *damagedealers
	
	// main player pointer and dimensions
	class Player* player;
	int playerWidth, playerHeight;

	// floor pointers and dimensions
	class Body* floor1, *floor2, *rightwall, *leftwall, *ceiling, *hidingspy;
	int floorWidth, floorHeight;

	// door to next scene
	class Body* progressionDoor;
	
public:
	Scene1(SDL_Window* sdlWindow_, GameManager* game_);
	~Scene1();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& sdlEvent);

};

#endif

