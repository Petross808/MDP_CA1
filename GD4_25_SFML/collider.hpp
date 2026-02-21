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
	bool m_is_dynamic;
	bool m_is_trigger;

protected:
	sf::Vector2f m_box_size;

public:
	Collider(float x, float y, Physics* physics, bool dynamic = false, bool trigger = false);
	~Collider();
	virtual bool CheckCollision(Collider* other) = 0;

	virtual bool CollideWith(Collider* other) = 0;
	virtual bool CollideWith(BoxCollider* other) = 0;
	virtual bool CollideWith(CircleCollider* other) = 0;
	virtual bool CollideWith(PolygonCollider* other) = 0;

	bool IsDynamic() const;
	bool IsTrigger() const;
	bool BoundingBoxOverlap(Collider* other);
	void ResolveCollision(Collider* other, sf::Vector2f& normal, float& depth);
};