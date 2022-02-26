#ifndef BODY_H
#define BODY_H
#include "Vector.h"
#include <SDL_image.h>

using namespace MATH;
class Body {
private:
	Vec3 pos;
	Vec3 vel;
	Vec3 accel;
	float mass;
	SDL_Surface *image;
	SDL_Texture* texture;
	SDL_Point getsize(SDL_Texture* texture);

	bool is_moving;

	// Test Run **************************************
	// Draw the object
	//virtual void draw() = 0;
	// Update the object
	//virtual void update() = 0;
	// remove anything that needs to be deleted
	//virtual void clean() = 0;
	//// getters for common variables
	//Transform* getTransform();
	//// getters and setters for physics properties
	//RigidBody* getRigidBody();

	// getters and setters for game object properties
	//int getWidth() const;
	//int getHeight() const;
	//void setWidth(int new_width);
	//void setHeight(int new_height);
	//Body getType() const;
	//void setType(Body new_type);
	//void setEnabled(bool state);
	//bool isEnabled() const;
	//void setVisible(bool state);
	//bool isVisible() const;
	//void setIsCentered(bool state);
	//bool isCentered() const;
	// Test Run **************************************

public:
	Body();
	Body(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_);
	~Body();
	void Update(float deltaTime);
	void ApplyForce(Vec3 force);
	Vec3 getPos() { return pos; }
	void isMoving(bool TorF) { is_moving = TorF; }
	void setImage(SDL_Surface *image_) { image = image_; }
	SDL_Surface* getImage() { return image; }
	SDL_Texture* getTexture() { return texture; }
	void setTexture(SDL_Texture  *texture_) { texture = texture_; }
	Vec3 getVelocity() { return vel; }
};
#endif
