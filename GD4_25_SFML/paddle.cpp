/*
* Petr Sulc - GD4b - D00261476
*/

#include "paddle.hpp"
#include "box_collider.hpp"
#include "circle_collider.hpp"
#include "polygon_collider.hpp"
#include "shape_node.hpp"


Paddle::Paddle(Physics* physics)
{
	//std::vector<sf::Vector2f> polygon{ {-30, 0},{30, 0},{0, 60} };
	
	std::vector<sf::Vector2f> polygon{
		{0.0000f, -1.0000f },
		{0.9511f, -0.3090f},
		{ 0.5878f,  0.8090f },
		{ -0.5878f,  0.8090f },
		{ -0.9511f, -0.3090f }
	};

	for (auto& vert : polygon)
	{
		vert *= 40.f;
	}
	

	setPosition(sf::Vector2f(150,150));
	std::unique_ptr<SceneNode> collider = std::make_unique<PolygonCollider>(0.f, 0.f, polygon, physics, true);
	AttachChild(std::move(collider));

	std::unique_ptr<ShapeNode> shape(new ShapeNode(polygon));
	AttachChild(std::move(shape));
}

void Paddle::ApplyMove(float x, float y)
{
	move(sf::Vector2f(x*3, y*3));
}

void Paddle::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
}

void Paddle::OnCollision(Collider& other)
{
}


