#include "Player.h"
#include "CollisionManager.h"

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

	image = NULL;
	texture = NULL;
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

SDL_Point Player::getsize(SDL_Texture* texture)
{
	SDL_Point size;
	SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
	return size;
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

	if (pos.x + (vel.x * deltaTime) < 0.0f) 
	{
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

// Test Run **************************************

//Transform* Player::getTransform()
//{
//	return nullptr;
//}
//
//RigidBody* Player::getRigidBody()
//{
//	return nullptr;
//}

//int Player::getWidth() const
//{
//	return m_width;
//}
//
//int Player::getHeight() const
//{
//	return m_height;
//}
//
//void Player::setWidth(int new_width)
//{
//	m_width = new_width;
//	new_width = getsize(texture).x;
//
//}
//
//void Player::setHeight(int new_height)
//{
//	m_height = new_height;
//	new_height = getsize(texture).y;
//}

//Player Player::getType() const
//{
//	return Player();
//}
//
//void Player::setType(Player new_type)
//{
//}

//void Player::setEnabled(bool state)
//{
//}
//
//bool Player::isEnabled() const
//{
//	return false;
//}
//
//void Player::setVisible(bool state)
//{
//}
//
//bool Player::isVisible() const
//{
//	return false;
//}
//
//void Player::setIsCentered(bool state)
//{
//}
//
//bool Player::isCentered() const
//{
//	return false;
//}

// Test Run **************************************
