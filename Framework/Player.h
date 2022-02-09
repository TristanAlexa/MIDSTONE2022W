#ifndef PLAYER_H
#define PLAYER_H
#include "Vector.h"
#include <SDL_image.h>

using namespace MATH;
class Player {
private:
	Vec3 pos;
	Vec3 vel;
	Vec3 accel;
	float rotationZ;
	float mass;
	float radius;
	SDL_Surface* image;
	SDL_Texture* texture;
	bool is_moving;


public:
	Player();
	Player(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_);
	~Player();

	void isMoving(bool TorF) { is_moving = TorF; }
	void Update(float deltaTime);
	void ApplyForce(Vec3 force);
	Vec3 getPos() { return pos; }
	void setImage(SDL_Surface* image_) { image = image_; }
	SDL_Surface* getImage() { return image; }
	SDL_Texture* getTexture() { return texture; }
	void setTexture(SDL_Texture* texture_) { texture = texture_; }
	Vec3 getVelocity() { return vel; }
	void setVelocity(Vec3 vel_) { vel = vel_; }  //overloaded operator
	float getRadius() { return radius; }
	float getMass() { return mass; }
	float getRotationZ() { return rotationZ; }

};
#endif

