/*
* Jakub Polacek - GD4b - D00260171
*/

#pragma once
#include "scene_node.hpp"
#include "physics.hpp"
#include "e_pickup_id.hpp"


class PickupSpawner : public SceneNode
{
public:
	PickupSpawner(float x, float y, Physics* physics_ptr, float spawn_time = 5);
	~PickupSpawner();
protected:
	virtual void UpdateCurrent(sf::Time dt, CommandQueue& commands) override;
private:
	Physics* m_physics_ptr;
	float m_spawn_time;
	float m_cooldown;
	bool m_has_pickup;

};