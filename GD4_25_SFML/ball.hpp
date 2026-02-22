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

protected:
	virtual void UpdateCurrent(sf::Time dt, CommandQueue& commands) override;

private:
	PhysicsBody m_physics_body;
	float m_start_delay;
};


