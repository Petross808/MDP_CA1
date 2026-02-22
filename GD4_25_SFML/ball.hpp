/*
* Petr Sulc - GD4b - D00261476
* Jakub Polacek - GD4b - D00260171
*/

#pragma once

#include "scene_node.hpp"
#include "physics.hpp"
#include "paddle.hpp"

class Ball : public SceneNode
{
public:
	Ball(float x, float y, float radius, Physics* physics);
	~Ball();
	virtual void OnCollision(Collider& other) override;
	void GivePickup(PickupID pickup_id);

private:
	PhysicsBody m_physics_body;
	Paddle* m_last_collided;
};


