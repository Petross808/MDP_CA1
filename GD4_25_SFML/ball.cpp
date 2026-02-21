/*
* Petr Sulc - GD4b - D00261476
*/

#include "ball.hpp"
#include "shape_node.hpp"
#include "box_collider.hpp"
#include "circle_collider.hpp"
#include "polygon_collider.hpp"

Ball::Ball(float x, float y, float width, float height, Physics* physics) :
	m_physics_body(this, physics, 1, 1000, 0, 1)
{
	setPosition(sf::Vector2f(x, y));
	std::unique_ptr<Collider> collider = std::make_unique<BoxCollider>(0.f, 0.f, width, height, physics, &m_physics_body);
	collider->SetLayer(CollisionLayer::kBall);
	AttachChild(std::move(collider));

	std::unique_ptr<ShapeNode> shape(new ShapeNode(width, height));
	AttachChild(std::move(shape));
}

Ball::Ball(float x, float y, float radius, Physics* physics):
	m_physics_body(this, physics, 1, 1000, 0, 1)
{
	setPosition(sf::Vector2f(x, y));
	std::unique_ptr<Collider> collider = std::make_unique<CircleCollider>(0.f, 0.f, radius, physics, &m_physics_body);
	collider->SetLayer(CollisionLayer::kBall);
	AttachChild(std::move(collider));

	std::unique_ptr<ShapeNode> shape(new ShapeNode(radius));
	AttachChild(std::move(shape));
}

Ball::Ball(float x, float y, std::vector<sf::Vector2f>& vertices, Physics* physics):
	m_physics_body(this, physics, 1, 1000, 0, 1)
{
	setPosition(sf::Vector2f(x, y));
	std::unique_ptr<Collider> collider = std::make_unique<PolygonCollider>(0.f, 0.f, vertices, physics, &m_physics_body);
	collider->SetLayer(CollisionLayer::kBall);
	AttachChild(std::move(collider));

	std::unique_ptr<ShapeNode> shape(new ShapeNode(vertices));
	AttachChild(std::move(shape));
}

Ball::~Ball() = default;