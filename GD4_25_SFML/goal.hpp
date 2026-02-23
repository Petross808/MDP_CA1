#pragma once
#include "scene_node.hpp"
#include "physics.hpp"

class Goal : public SceneNode
{
public:
	Goal(int team, float x, float y, float width, float height, Physics* physics);
	~Goal();

	virtual void OnCollision(Collider& other, CommandQueue& command_queue) override;

private:
	int m_team;
	Command m_one_score;
	Command m_two_score;
	Command m_reset_ball;
};


