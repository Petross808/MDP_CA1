/*
* Petr Sulc - GD4b - D00261476
*/

#pragma once
#include "scene_node.hpp"
#include "physics.hpp"

class Wall : public SceneNode
{
public:
	Wall(float x, float y, float width, float height, Physics* physics);
	Wall(float x, float y, float radius, Physics* physics);
	Wall(float x, float y, std::vector<sf::Vector2f>& vertices, Physics* physics);
	~Wall();
};

