#include "Player.h"

Player::Player()
{
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;

	vel.x = 0.0f;
	vel.y = 0.0f;
	vel.z = 0.0f;

	accel.x = 0.0f;
	accel.y = 0.0f;
	accel.z = 0.0f;

	mass = UNI_MASS;
	gravity = -GRAVITY;

	isMoving(false);
	
}

Player::Player(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_)
{
	pos = pos_;
	vel = vel_;
	accel = accel_;
	mass = mass_;
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{


	//Update position due to acceleration forces
	accel.x = force.x / mass;
	accel.y = gravity + force.y / mass;
	vel.x += accel.x * deltaTime;
	vel.y += accel.y * deltaTime;

	//wall and floor collisions to test player movement
	if (pos.y < 5.0f) {
		vel.y = 0.0f;
	}
	if (pos.y > 15.0f) {
		vel.y = -vel.y;
	}
	if (pos.x < 0.0f) {
		vel.x = -vel.x;
	}
	if (pos.x > 27.0f) {
		vel.x = -vel.x;
	}

	pos += vel * deltaTime;

}
