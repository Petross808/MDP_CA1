/*
* Petr Sulc - GD4b - D00261476
* Jakub Polacek - GD4b - D00260171
*/

#include "ball.hpp"
#include "shape_node.hpp"
#include "circle_collider.hpp"
#include "sound_node.hpp"

Ball::Ball(float x, float y, float radius, Physics* physics, sf::Texture* texture) :
	m_last_collided(),
	SceneNode(ReceiverCategories::kBall),
	m_physics_body(this, physics, 1, 1000, 0, 1.1f),
	m_bounce_sound(DerivedAction<SoundNode>([this](SoundNode& s, sf::Time dt) { s.PlaySound(SoundID::kBounce, GetWorldPosition());}), ReceiverCategories::kSoundNode),
	m_start_delay(3)
{
	setPosition(sf::Vector2f(x, y));
	std::unique_ptr<Collider> collider = std::make_unique<CircleCollider>(0.f, 0.f, radius, physics, &m_physics_body);
	collider->SetLayer(CollisionLayer::kBall);
	AttachChild(std::move(collider));

	std::unique_ptr<ShapeNode> shape(new ShapeNode(radius));
	if (texture != nullptr)
	{
		shape->SetTexture(*texture);
	}
	AttachChild(std::move(shape));
}

Ball::~Ball() = default;

void Ball::OnCollision(Collider& other, CommandQueue& command_queue)
{
	Paddle* paddle = dynamic_cast<Paddle*>(other.GetParent());
	if (paddle != nullptr)
	{
		m_last_collided = paddle;
	}
	command_queue.Push(m_bounce_sound);
}

void Ball::GivePickup(PickupID pickup_id)
{
	if (m_last_collided != nullptr)
	{
		m_last_collided->SetPickup(pickup_id);
  }
}

void Ball::UpdateCurrent(sf::Time dt, CommandQueue& commands)
{
	if (m_start_delay <= 0) return;

	m_start_delay -= dt.asSeconds();

	if (m_start_delay <= 0)
	{
		m_physics_body.AddForce(-7500, 0);
	}
}
