/*
* Petr Sulc - GD4b - D00261476
* Jakub Polacek - GD4b - D00260171
*/

#pragma once
#include "scene_node.hpp"
#include "physics.hpp"

class Goal : public SceneNode
{
public:
	Goal(float x, float y, float width, float height, Physics* physics, sf::Texture* texture = nullptr);
	~Goal();

	virtual void OnCollision(Collider& other, CommandQueue& command_queue) override;
};


