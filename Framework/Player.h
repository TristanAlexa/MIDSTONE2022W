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
	Vec3 force;

	float rotationZ;
	float mass;
	float gravity;
	float radius;

	SDL_Surface* image;
	SDL_Texture* texture;
	bool is_moving;
	bool is_grounded;

public:
	Player();
	Player(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_);
	~Player();

	void isMoving(bool TorF) { is_moving = TorF; }
	void Update(float deltaTime);

	//Force
	inline void ApplyForce(Vec3 force_) { force = force_; }
	inline void ApplyForceX(float Fx) { force.x = Fx; }
	inline void ApplyForceY(float Fy) { force.y = Fy; }
	inline void UnsetForceX() { force.x = 0.0f; }
	inline void UnsetForceY() { force.y = 0.0f; }

	//Getter-Setters
	Vec3 getPos() { return pos; }
	Vec3 getVelocity() { return vel; }
	void setVelocity(Vec3 vel_) { vel = vel_; }  //overloaded operator
	void setPosition(Vec3 pos_) { pos = pos_; }
	Vec3 getAcceleration() { return accel; }
	float getRadius() { return radius; }
	float getMass() { return mass; }
	float getRotationZ() { return rotationZ; }\
	inline void setMass(float mass_) { mass = mass_; }
	inline void setGravity(float gravity_) { gravity = gravity_; }

	void setImage(SDL_Surface* image_) { image = image_; }
	SDL_Surface* getImage() { return image; }
	void setTexture(SDL_Texture* texture_) { texture = texture_; }
	SDL_Texture* getTexture() { return texture; }
};
#endif

