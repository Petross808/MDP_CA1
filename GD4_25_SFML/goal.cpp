#include "goal.hpp"
#include "box_collider.hpp"
#include "shape_node.hpp"

Goal::Goal(float x, float y, float width, float height, Physics* physics)
{
	setPosition(sf::Vector2f(x, y));
	std::unique_ptr<Collider> collider = std::make_unique<BoxCollider>(0.f, 0.f, width, height, physics, nullptr, true);
	collider->SetLayer(CollisionLayer::kGoal);
	collider->SetIgnoreLayers(CollisionLayer::kPlayer);
	AttachChild(std::move(collider));

	std::unique_ptr<ShapeNode> shape(new ShapeNode(width, height));
	shape->SetColor(sf::Color::Magenta);
	AttachChild(std::move(shape));
}

Goal::~Goal() = default;

void Goal::OnCollision(Collider& other, CommandQueue& command_queue)
{
	//TODO end the game
}
