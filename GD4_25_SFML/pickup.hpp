/*
* Jakub Polacek - GD4b - D00260171
*/

#pragma once
#include "scene_node.hpp"
#include "physics.hpp"


class Pickup : public SceneNode
{
public:
	Pickup(float x, float y, float radius, Physics* physics, sf::Texture* texture = nullptr);
	~Pickup();
	virtual void OnCollision(Collider& other) override;
};