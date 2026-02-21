/*
* Petr Sulc - GD4b - D00261476
*/

#include "collider.hpp"

Collider::Collider(float x, float y, Physics* physics, bool dynamic, bool trigger) :
	m_physics(physics),
	m_is_dynamic(dynamic),
	m_is_trigger(trigger)
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

bool Collider::IsDynamic() const
{
	return m_is_dynamic;
}

bool Collider::IsTrigger() const
{
	return m_is_trigger;
}

bool Collider::BoundingBoxOverlap(Collider* other)
{
	sf::Vector2f min(GetWorldPosition());
	sf::Vector2 max(min + m_box_size);

	sf::Vector2 otherMin(other->GetWorldPosition());
	sf::Vector2 otherMax(otherMin + other->m_box_size);

	return (min.x <= otherMax.x && max.x >= otherMin.x && min.y <= otherMax.y && max.y >= otherMin.y);
}

void Collider::ResolveCollision(Collider* other, sf::Vector2f& normal, float& depth)
{
	if (m_is_trigger || other->m_is_trigger)
		return;

	if (m_is_dynamic && other->m_is_dynamic)
	{
		GetParent()->move(-normal * depth / 2.f);
		other->GetParent()->move(normal * depth / 2.f);
	}
	else if (m_is_dynamic)
	{
		GetParent()->move(-normal * depth);
	}
	else
	{
		other->GetParent()->move(normal * depth);
	}
}
