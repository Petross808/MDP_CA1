/*
* Petr Sulc - GD4b - D00261476
*/

#include "paddle.hpp"
#include "box_collider.hpp"
#include "circle_collider.hpp"
#include "polygon_collider.hpp"
#include "shape_node.hpp"
#include "sound_node.hpp"
#include "utility.hpp"


Paddle::Paddle(int playerId, int characterId, float x, float y, Physics* physics, SoundPlayer& sounds, sf::Texture* texture) :
	Pawn(playerId),
	m_speed(1500),
	m_move_vector(),
	m_physics_body(this, physics, 10000.f, 1500, 2.f, 0.1f, 0.8f),
	m_sounds(sounds),
	m_pickup_id(PickupID::kNone)
{
	std::vector<sf::Vector2f> polygon;
	switch (characterId)
	{
	case 0:
		polygon = {
			{ 0.f, 0.f },
			{ 0.f, -3.f },
			{ 1.f, -3.f },
			{ 1.f, 0.f }
		};
		break;
	case 1:
		polygon = {
			{0, 2}, 
			{1, 0.75f}, 
			{1, -0.75f}, 
			{0, -2}, 
			{-1, -0.75f}, 
			{-1, 0.75f} };
		m_physics_body = PhysicsBody(this, physics, 10000.f, 1500, 2.5f, 0.1f, 0.5f);
		m_speed = 2000;
		break;
	case 2:
		polygon = {
			{ 0.f, 3.f },
			{ 1.f, 0.f },
			{ 0.f, -3.f },
			{ -1.f, 0.f }
		};
		m_physics_body = PhysicsBody(this, physics, 10000.f, 1500, 2.f, 0.1f, 0.2f);
		break;
	case 3:
		polygon = {
			{ 0.f, 0.f },
			{ 0.f, -2.f },
			{ 0.5f, -2.f },
			{ 0.5f, 0.f }
		};
		m_physics_body = PhysicsBody(this, physics, 5000.f, 5000.f, 1.5f, 0.2f, 2.f);
		m_speed = 10000;
		break;
	default:
		break;
	}
	
	for (auto& vert : polygon)
	{
		vert *= 50.f;
	}

	sf::Vector2f center = Utility::GetPolygonBound(polygon).getCenter();

	setPosition(sf::Vector2f(x - center.x , y - center.y));
	m_physics_body.SetAsKinematic();

	std::unique_ptr<Collider> collider = std::make_unique<PolygonCollider>(0.f, 0.f, polygon, physics, &m_physics_body);
	collider->SetLayer(CollisionLayer::kPlayer);
	collider->SetIgnoreLayers(CollisionLayer::kPlayer);
	AttachChild(std::move(collider));

	std::unique_ptr<ShapeNode> shape(new ShapeNode(polygon));
	if (texture != nullptr)
	{
		shape->SetTexture(*texture);
	}
	AttachChild(std::move(shape));
}

void Paddle::ApplyMove(float x, float y)
{
	m_move_vector.x += x;
	m_move_vector.y += y;
}

// Jakub Polacek - GD4b - D00260171
void Paddle::SetPickup(PickupID pickup_id)
{
	m_pickup_id = pickup_id;
}

// Jakub Polacek - GD4b - D00260171
void Paddle::UsePickup()
{
	switch (m_pickup_id)
	{
		case PickupID::kNone:
			break;
		case PickupID::kSpeedBoost:
		{
			sf::Vector2f boost = (m_move_vector.normalized() * 30000.f);
			m_physics_body.AddForce(boost.x, boost.y);
			m_sounds.Play(SoundID::kPickupUse);
			m_pickup_id = PickupID::kNone;
			break;
		}
		default:
			break;
	}
}

void Paddle::UpdateCurrent(sf::Time dt, CommandQueue& commands)
{
	if (m_move_vector != sf::Vector2f())
	{
		sf::Vector2f force = m_move_vector.normalized() * 1500.f;
		m_physics_body.AddForce(force.x, force.y);
		m_move_vector = { 0, 0 };
	}

	m_physics_body.Simulate(dt);
}

void Paddle::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
}

void Paddle::OnCollision(Collider& other, CommandQueue& command_queue)
{
}


