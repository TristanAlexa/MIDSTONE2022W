#ifndef PLAYER_H
#define PLAYER_H
#include "Vector.h"
#include <SDL_image.h>

//defining constants for player and enemy bodies
#define UNI_MASS 1.0f
#define GRAVITY 9.8f

using namespace MATH;
class Player {
private:
	Vec3 pos;
	Vec3 vel;
	Vec3 accel;
	float gravity;

	SDL_Surface* image;
	SDL_Texture* texture;
	bool is_moving;
	bool is_grounded;

public:
	Player();
	Player(Vec3 pos_, Vec3 vel_, Vec3 accel_);
	~Player();

	void isMoving(bool TorF) { is_moving = TorF; }
	//void isGrounded(bool TorF) { is_grounded = TorF; }
	bool isGrounded();
	void Update(float deltaTime);

	//Getter-Setters
	Vec3 getPos() { return pos; }
	Vec3 getVelocity() { return vel; }
	void setVelocity(Vec3 vel_) { vel = vel_; }  //overloaded operator
	void setVelocityX(float Vx) { vel.x = Vx; }
	void setVelocityY(float Vy) { vel.y = Vy; }
	void setPosition(Vec3 pos_) { pos = pos_; }
	Vec3 getAcceleration() { return accel; }
	inline void setGravity(float gravity_) { gravity = gravity_; }

	void setImage(SDL_Surface* image_) { image = image_; }
	SDL_Surface* getImage() { return image; }
	void setTexture(SDL_Texture* texture_) { texture = texture_; }
	SDL_Texture* getTexture() { return texture; }
};
#endif

