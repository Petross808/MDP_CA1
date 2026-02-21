/*
* Petr Sulc - GD4b - D00261476
*/

#include "paddle.hpp"
#include "box_collider.hpp"
#include "circle_collider.hpp"
#include "polygon_collider.hpp"
#include "shape_node.hpp"
#include <iostream>


Paddle::Paddle(Physics* physics) :
	m_move_vector(),
	m_physics_body(this, physics, 50.f, 1000, 2.f, 0.1f),
	m_pickup_id(PickupID::kNone)
{
	std::vector<sf::Vector2f> polygon;
	switch (3)
	{
	case 1:
		polygon = {
			{ 0.0000f, 0.0000f },
			{ 0.0000f, -1.0000f },
			{ 1.0000f, -1.0000f },
			{ 1.0000f, 0.0000f }
		};
		break;
	case 2:
		polygon = { {-1, 0},{1, 0},{0, 2} };
		break;
	case 3:
		polygon = {
			{ 0.0000f, -1.0000f },
			{ 0.9511f, -0.3090f },
			{ 0.5878f, 0.8090f },
			{ -0.5878f, 0.8090f },
			{ -0.9511f, -0.3090f }
		};
		break;
	default:
		break;
	}
	
	for (auto& vert : polygon)
	{
		vert *= 40.f;
	}

	setPosition(sf::Vector2f(150,150));
	m_physics_body.SetAsKinematic();

	std::unique_ptr<Collider> collider = std::make_unique<PolygonCollider>(0.f, 0.f, polygon, physics, &m_physics_body);
	collider->SetLayer(CollisionLayer::kPlayer);
	collider->SetIgnoreLayers(CollisionLayer::kWall | CollisionLayer::kPlayer);
	AttachChild(std::move(collider));

	std::unique_ptr<ShapeNode> shape(new ShapeNode(polygon));
	AttachChild(std::move(shape));
}

void Paddle::ApplyMove(float x, float y)
{
	m_move_vector.x += x;
	m_move_vector.y += y;
}

void Paddle::UsePickup()
{
	//TODO pickup behaviour implementation
	switch (m_pickup_id)
	{
		case PickupID::kNone:
			break;
		case PickupID::kSpeedBoost:
			m_move_vector.x += 5000;
			m_move_vector.y += 5000;
			break;
		default:
			throw std::invalid_argument("error while trying to use pickups");
			break;
	}
}

void Paddle::UpdateCurrent(sf::Time dt, CommandQueue& commands)
{
	if (m_move_vector != sf::Vector2f())
	{
		sf::Vector2f force = m_move_vector.normalized() * 1000.f;
		m_physics_body.AddForce(force.x, force.y);
		m_move_vector = { 0, 0 };
	}

	m_physics_body.Simulate(dt);
}

void Paddle::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
}

void Paddle::OnCollision(Collider& other)
{
}


