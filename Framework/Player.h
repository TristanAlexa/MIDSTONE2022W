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
	// Vec3 size;

	float gravity;
	float mass;

	float rotationZ;
	float radius;

	SDL_Surface* image;
	SDL_Texture* texture;
	SDL_Point getsize(SDL_Texture* texture);
	bool is_moving;
	bool is_grounded;

	// Test Run
		// Draw the object
	virtual void draw() = 0;

	// Update the object
	virtual void update() = 0;

	// remove anything that needs to be deleted
	virtual void clean() = 0;

	// getters for common variables
	//Transform* getTransform();

	//// getters and setters for physics properties
	//RigidBody* getRigidBody();

	// getters and setters for game object properties
	int getWidth() const;
	int getHeight() const;
	void setWidth(int new_width);
	void setHeight(int new_height);
	//Player getType() const;
	//void setType(Player new_type);

	void setEnabled(bool state);
	bool isEnabled() const;

	void setVisible(bool state);
	bool isVisible() const;

	void setIsCentered(bool state);
	bool isCentered() const;

public:
	Player();
	Player(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_);
	~Player();

	void isMoving(bool TorF) { is_moving = TorF; }
	//void isGrounded(bool TorF) { is_grounded = TorF; }
	bool isGrounded();
	void Update(float deltaTime);

	//Force
	inline void ApplyForce(Vec3 force_) { force = force_; }
	inline void ApplyForceX(float Fx) { force.x = Fx; }
	inline void ApplyForceY(float Fy) { force.y = Fy; }
	inline void UnsetForceX() { force.x = 0.0f; }
	inline void UnsetForceY() { force.y = 0.0f; }

	//Getter-Setters
	// Vec3 getsize() { return size; }
	Vec3 getPos() { return pos; }
	Vec3 getVelocity() { return vel; }
	void setVelocity(Vec3 vel_) { vel = vel_; }  //overloaded operator
	void setVelocityX(float Vx) { vel.x = Vx; }
	void setVelocityY(float Vy) { vel.y = Vy; }
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

	// Test Run

	// transform component
	/*Transform m_transform;*/

	// rigid body component
	/*RigidBody m_rigidBody;*/

	// size variables
	int m_width;
	int m_height;
	/*GameObjectType m_type;*/

	bool m_enabled;
	bool m_visible;
	bool m_isCentered;
};
#endif

