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

	mass = 1.0f;
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

	if (is_moving == false) {
		return;
	}
	pos += (vel * deltaTime); + (0.5 * accel * deltaTime * deltaTime);
	vel += (accel * deltaTime);

	//wall and floor collisions to test player movement
	if (pos.y < 0.0f) {
		vel.y = -vel.y;
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
}

void Player::ApplyForce(Vec3 force)
{
	accel = force / mass;
}