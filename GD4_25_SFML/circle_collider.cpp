/*
* Petr Sulc - GD4b - D00261476
*/

#include "box_collider.hpp"
#include "circle_collider.hpp"
#include "polygon_collider.hpp"
#include "utility.hpp"

CircleCollider::CircleCollider(float x, float y, float radius, Physics* physics) : Collider(x, y, physics), m_radius(radius)
{
	m_box_size.x = radius * 2;
	m_box_size.y = radius * 2;
}

bool CircleCollider::CheckCollision(Collider* other)
{
	return other->CollideWith(this);
}

bool CircleCollider::CollideWith(Collider* other)
{
	return true;
}

bool CircleCollider::CollideWith(BoxCollider* other)
{
	sf::Vector2f center(GetCenter());
	sf::Vector2f boxMin(other->GetWorldPosition());
	sf::Vector2f boxMax(boxMin + other->GetBoxSize());
	sf::Vector2f closest(std::clamp(center.x, boxMin.x, boxMax.x), std::clamp(center.y, boxMin.y, boxMax.y));

	return Utility::SqrLength(center - closest) < m_radius * m_radius;
}

bool CircleCollider::CollideWith(CircleCollider* other)
{
	float combinedRadius = m_radius + other->m_radius;
	return Utility::SqrLength(GetCenter() - other->GetCenter()) <= combinedRadius * combinedRadius;
}

bool CircleCollider::CollideWith(PolygonCollider* other)
{
	return other->CollideWith(this);
}

float CircleCollider::GetRadius() const
{
	return m_radius;
}

sf::Vector2f CircleCollider::GetCenter() const
{
	return GetWorldPosition() + sf::Vector2f{m_radius, m_radius};
}
