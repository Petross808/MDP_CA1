/*
* Jakub Polacek - GD4b - D00260171
*/

#include "pickup.hpp"
#include "shape_node.hpp"
#include "circle_collider.hpp"


Pickup::Pickup(float x, float y, float radius, Physics* physics, sf::Texture* texture)
{
	setPosition(sf::Vector2f(x, y));
	std::unique_ptr<Collider> collider = std::make_unique<CircleCollider>(0.f, 0.f, radius, physics);
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

	//TODO move to player

	//TODO remove from scene

}

Pickup::~Pickup() = default;