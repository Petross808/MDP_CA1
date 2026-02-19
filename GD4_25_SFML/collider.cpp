/*
* Petr Sulc - GD4b - D00261476
*/

#include "collider.hpp"

Collider::Collider(float x, float y, Physics* physics) : m_physics(physics)
{
	m_physics->Register(this);
	setPosition({x, y});
}

Collider::~Collider()
{
	m_physics->Unregister(this);
}

bool Collider::CheckCollision(Collider* other)
{
	return other->CollideWith(this);
}

bool Collider::BoundingBoxOverlap(Collider* other)
{
	sf::Vector2f min(GetWorldPosition());
	sf::Vector2 max(min + m_box_size);

	sf::Vector2 otherMin(other->GetWorldPosition());
	sf::Vector2 otherMax(otherMin + other->m_box_size);

	return (min.x <= otherMax.x && max.x >= otherMin.x && min.y <= otherMax.y && max.y >= otherMin.y);
}
