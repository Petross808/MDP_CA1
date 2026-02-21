/*
* Petr Sulc - GD4b - D00261476
*/

#include "paddle.hpp"
#include "box_collider.hpp"
#include "circle_collider.hpp"
#include "polygon_collider.hpp"
#include "shape_node.hpp"


Paddle::Paddle(Physics* physics) : m_move_vector()
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
	std::unique_ptr<SceneNode> collider = std::make_unique<PolygonCollider>(0.f, 0.f, polygon, physics, true);
	AttachChild(std::move(collider));

	std::unique_ptr<ShapeNode> shape(new ShapeNode(polygon));
	AttachChild(std::move(shape));
}

void Paddle::ApplyMove(float x, float y)
{
	m_move_vector.x += x;
	m_move_vector.y += y;
}

void Paddle::UpdateCurrent(sf::Time dt, CommandQueue& commands)
{
	if (m_move_vector != sf::Vector2f())
	{
		move(m_move_vector.normalized() * 3.f);
		m_move_vector = { 0, 0 };
	}
}

void Paddle::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
}

void Paddle::OnCollision(Collider& other)
{
}


