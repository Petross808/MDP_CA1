#pragma once
#include "scene_node.hpp"
#include "physics.hpp"

class Goal : public SceneNode
{
public:
	Goal(float x, float y, float width, float height, Physics* physics);
	~Goal();

	virtual void OnCollision(Collider& other) override;
};


