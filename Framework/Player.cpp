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
	accel.y = -GRAVITY;
	accel.z = 0.0f;

	gravity = -GRAVITY;

	is_moving = false;
	is_grounded = false;
}

Player::Player(Vec3 pos_, Vec3 vel_, Vec3 accel_)
{
	pos = pos_;
	vel = vel_;
	accel = accel_;
}

Player::~Player()
{
}


bool Player::isGrounded()
{
	if (pos.y <= 5.0f) {
		is_grounded = true;
		return true;
	}
	else {
		is_grounded = false;
		return false;
	}
}

void Player::Update(float deltaTime)
{


	//Update position due to acceleration forces
	vel.y += accel.y * deltaTime;

	//wall and floor collisions to test player movement
	// if would collide, then stop, if wouldn't collide, update normally
	if (pos.y + (vel.y * deltaTime) < 5.0f)
	{
		pos.y = 5.0f;
		
	}
	else if (pos.y + (vel.y * deltaTime) > 15.0f)
	{
		pos.y = 15.0f;
	}
	else
	{
		pos.y += vel.y * deltaTime;
	}

	if (pos.x + (vel.x * deltaTime) < 0.0f) {
		pos.x = 0.0f;
		
	}
	else if (pos.x + (vel.x * deltaTime) > 27.0f)
	{
		pos.x = 27.0f;
		
	}
	else
	{
		pos.x += vel.x * deltaTime;
	}


}
