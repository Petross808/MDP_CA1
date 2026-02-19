/*
* Petr Sulc - GD4b - D00261476
*/

#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "physics.hpp"
#include "scene_node.hpp"

class Physics;
class BoxCollider;
class CircleCollider;
class PolygonCollider;

class Collider : public SceneNode
{
private:
	Physics* m_physics;

protected:
	sf::Vector2f m_box_size;

public:
	Collider(float x, float y, Physics* physics);
	~Collider();
	virtual bool CheckCollision(Collider* other) = 0;

	virtual bool CollideWith(Collider* other) = 0;
	virtual bool CollideWith(BoxCollider* other) = 0;
	virtual bool CollideWith(CircleCollider* other) = 0;
	virtual bool CollideWith(PolygonCollider* other) = 0;

	bool BoundingBoxOverlap(Collider* other);
};