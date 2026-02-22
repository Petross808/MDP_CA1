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
	Ball(float x, float y, float radius, Physics* physics, sf::Texture* texture = nullptr);
	~Ball();
	virtual void OnCollision(Collider& other, CommandQueue& command_queue) override;
	void GivePickup(PickupID pickup_id);

protected:
	virtual void UpdateCurrent(sf::Time dt, CommandQueue& commands) override;

private:
	PhysicsBody m_physics_body;
	Paddle* m_last_collided;
	float m_start_delay;
	Command m_bounce_sound;
};


