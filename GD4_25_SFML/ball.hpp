/*
* Petr Sulc - GD4b - D00261476
*/

#pragma once

#include "scene_node.hpp"
#include "physics.hpp"

class Ball : public SceneNode
{
public:
	Ball(float x, float y, float width, float height, Physics* physics);
	Ball(float x, float y, float radius, Physics* physics);
	Ball(float x, float y, std::vector<sf::Vector2f>& vertices, Physics* physics);
	~Ball();

private:
	PhysicsBody m_physics_body;
};


