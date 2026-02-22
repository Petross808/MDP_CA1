/*
* Jakub Polacek - GD4b - D00260171
*/

#include "pickup.hpp"
#include "shape_node.hpp"
#include "circle_collider.hpp"
#include "ball.hpp"


Pickup::Pickup(float x, float y, float radius, Physics* physics, PickupID pickup_id, sf::Texture* texture) :
	m_pickup_id(pickup_id),
	m_is_destroyed(false)
{
	setPosition(sf::Vector2f(x, y));
	std::unique_ptr<Collider> collider = std::make_unique<CircleCollider>(0.f, 0.f, radius, physics, nullptr, true);
	collider->SetLayer(CollisionLayer::kPickup);
	AttachChild(std::move(collider));

	std::unique_ptr<ShapeNode> shape(new ShapeNode(radius));
	if (texture != nullptr)
	{
		shape->SetTexture(*texture);
	}
	AttachChild(std::move(shape));
}

void Pickup::OnCollision(Collider& other)
{
	Ball* ball = dynamic_cast<Ball*>(other.GetParent());
	if (ball != nullptr)
	{
		ball->GivePickup(m_pickup_id);
		m_is_destroyed = true;
	}
}

bool Pickup::IsDestroyed() const
{
	return m_is_destroyed;
}

Pickup::~Pickup() = default;