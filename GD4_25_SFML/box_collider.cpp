/*
* Petr Sulc - GD4b - D00261476
*/

#include "box_collider.hpp"
#include "circle_collider.hpp"
#include "polygon_collider.hpp"

BoxCollider::BoxCollider(float x, float y, float width, float height, Physics* physics, bool dynamic) : 
	Collider(x, y, physics, dynamic)
{
	m_box_size.x = width;
	m_box_size.y = height;
}

BoxCollider::~BoxCollider()
{
}

bool BoxCollider::CheckCollision(Collider* other)
{
	return other->CollideWith(this);
}

bool BoxCollider::CollideWith(Collider* other)
{
	return true;
}

bool BoxCollider::CollideWith(BoxCollider* other)
{
	return true;
}

bool BoxCollider::CollideWith(CircleCollider* other)
{
	return other->CollideWith(this);
}

bool BoxCollider::CollideWith(PolygonCollider* other)
{
	return other->CollideWith(this);
}

sf::Vector2f BoxCollider::GetBoxSize() const
{
	return m_box_size;
}