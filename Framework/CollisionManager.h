#pragma once
#ifndef __COLLISION_MANAGER__
#define __COLLISION_MANAGER__

// core libraries
#include <iostream>

#include "Body.h"
#include "GameObject.h"
#include "Player.h"
#include <GLM/gtx/norm.hpp>


class CollisionManager
{
public:
	// Current collision test method being used
	static bool checkCollision(Player* player, Body* collidedObject);

	static int squaredDistance(glm::vec2 p1, glm::vec2 p2);
	static bool squaredRadiusCheck(GameObject* object1, GameObject* object2);

	static bool AABBCheck(Player* object1, Body* object2);

	static bool lineLineCheck(glm::vec2 line1_start, glm::vec2 line1_end, glm::vec2 line2_start, glm::vec2 line2_end);

	static bool lineRectCheck(glm::vec2 line_start, glm::vec2 line_end, glm::vec2 rect_start, float rect_width, float rect_height);
	static bool lineRectEdgeCheck(glm::vec2 line_start, glm::vec2 rect_start, float rect_width, float rect_height);


	static int minSquaredDistanceLineLine(glm::vec2 line1_start, glm::vec2 line1_end, glm::vec2 line2_start, glm::vec2 line2_end);
	static bool lineAABBCheck(Player* object1, GameObject* object2);

	static int circleAABBsquaredDistance(glm::vec2 circle_centre, int circle_radius, glm::vec2 box_start, int box_width, int box_height);
	static bool circleAABBCheck(GameObject* object1, GameObject* object2);

	static bool pointRectCheck(glm::vec2 point, glm::vec2 rect_start, float rect_width, float rect_height);

	//static bool LOSCheck(Agent* agent, glm::vec2 end_point, const std::vector<DisplayObject*>& objects, DisplayObject* target);

	static void rotateAABB(GameObject* object1, float angle);

private:
	CollisionManager();
	~CollisionManager();
};

#endif /* defined (__COLLISION_MANAGER__) */
