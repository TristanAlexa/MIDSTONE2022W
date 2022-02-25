#include "Body.h"


SDL_Point Body::getsize(SDL_Texture* texture)
{
	return SDL_Point();
}

Body::Body(){
	pos.x = 15.0f;
	pos.y = 12.5f;
	pos.z = 0.0f;

	vel.x = -5.0f;
	vel.y = 0.0f;
	vel.z = 0.0f;

	accel.x = 0.0f;
	accel.y = -9.81f;
	accel.z = 0.0f;

	mass = 0.0f;
	isMoving(false);
}

Body::Body(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_) {
	pos = pos_;
	vel = vel_;
	accel = accel_;
	mass = mass_;
}

Body::~Body(){

}
void Body::ApplyForce(Vec3 force) { //acceleration due to the force
	accel = force / mass;
}
void Body::Update(float deltaTime){
	if (is_moving == false) {
		return;
	}
	Vec3 gravity(0.0f, -9.81f, 0.0f); // acceleration due to gravity - adds gravity to accel
	pos += (vel * deltaTime) + (0.5 * accel * deltaTime * deltaTime) + (0.5 * gravity * deltaTime * deltaTime);
	vel += (accel * deltaTime) + (gravity * deltaTime);

	if (pos.y < 0.0f) {
		vel.y = -vel.y;
	}
	if (pos.x < 0.0f) {
		vel.x = -vel.x;
	}
	if (pos.x > 29.0f) {
		vel.x = -vel.x;
	}
}

//Transform* Body::getTransform()
//{
//	return nullptr;
//}
//
//RigidBody* Body::getRigidBody()
//{
//	return nullptr;
//}

int Body::getWidth() const
{
	return 0;
}

int Body::getHeight() const
{
	return 0;
}

void Body::setWidth(int new_width)
{
	new_width = getsize(texture).x;
}

void Body::setHeight(int new_height)
{
	new_height = getsize(texture).y;
}

//Body Body::getType() const
//{
//	return Body();
//}
//
//void Body::setType(Body new_type)
//{
//}

void Body::setEnabled(bool state)
{
}

bool Body::isEnabled() const
{
	return false;
}

void Body::setVisible(bool state)
{
}

bool Body::isVisible() const
{
	return false;
}

void Body::setIsCentered(bool state)
{
}

bool Body::isCentered() const
{
	return false;
}
