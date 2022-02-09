#include "Body.h"


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
