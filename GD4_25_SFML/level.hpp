/*
* Jakub Polacek - GD4b - D00260171
*/

#pragma once
#include "scene_node.hpp"
#include "physics.hpp"
#include "resource_identifiers.hpp"

class Level
{
public:
	static void CreateBounds(SceneNode* root, Physics* physics, sf::FloatRect world_bounds, float wall_width);

	static void CreateClassic(SceneNode* root, Physics* physics, TextureHolder* texture_holder, sf::FloatRect world_bounds);

};