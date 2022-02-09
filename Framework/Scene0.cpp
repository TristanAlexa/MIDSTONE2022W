#include "Scene0.h"
#include <SDL.h>
#include <SDL_image.h>
Scene0::Scene0(SDL_Window* sdlWindow_){
	window = sdlWindow_;
	flappybird = new Body(Vec3(0.0f, 15.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, -9.8f, 0.0f), 1.0f);
	cliff = new Body(Vec3(0.0f, 15.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f);
}


Scene0::~Scene0(){
	delete flappybird;
	delete cliff;
}

bool Scene0::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, 30.0f, 0.0f, 15.0f, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* ballImage = IMG_Load("textures/flappybird.png");
	if(ballImage == nullptr) {
		printf("Can't open textures/ball.png\n");
		return false;
	}
	flappybird->setImage(ballImage);

	SDL_Surface* cliffImage = IMG_Load("textures/cliff.png");
	if (cliffImage == nullptr) {
		printf("Can't open textures/cliff.png\n");
		return false;
	}
	cliff->setImage(cliffImage);
	return true;
}

void Scene0::OnDestroy() {}

void Scene0::Update(const float deltaTime) {
	flappybird->Update(deltaTime);
}

void Scene0::HandleEvents(const SDL_Event& sdlEvent) {
	if (sdlEvent.type == SDL_EventType::SDL_KEYDOWN) {
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_D) {
			printf("Got the d key\n");
			flappybird->ApplyForce(Vec3(10.0f, 0.0f, 0.0f));
			flappybird->isMoving(true);
		}
	}
	else if (sdlEvent.type == SDL_EventType::SDL_KEYUP) {
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_D) {
			flappybird->ApplyForce(Vec3(0.0f, 0.0f, 0.0f));
		}
	}
}
void Scene0::Render() {
	SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 173, 216, 230)); //colour black
	SDL_Rect square;
	Vec3 screenCoords;

	screenCoords = projectionMatrix * cliff->getPos();
	square.x = (int)screenCoords.x; /// We must update this with C11 typecasting - SSF
	square.y = (int)screenCoords.y;
	square.w = 30;
	square.h = 30;
	SDL_BlitSurface(cliff->getImage(), nullptr, screenSurface, &square);


	screenCoords = projectionMatrix * flappybird->getPos();
	square.x = (int) screenCoords.x; /// We must update this with C11 typecasting - SSF
	square.y = (int) screenCoords.y;
	square.w = 30;
	square.h = 30;
	SDL_BlitSurface(flappybird->getImage(), nullptr, screenSurface,&square);

	SDL_UpdateWindowSurface(window);
}