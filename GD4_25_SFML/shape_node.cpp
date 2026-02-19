/*
* Petr Sulc - GD4b - D00261476
*/

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

#include "shape_node.hpp"
#include <memory>

ShapeNode::ShapeNode(float width, float height) : m_shape(new sf::RectangleShape({ width, height })), m_is_colliding(false)
{
}

ShapeNode::ShapeNode(float radius) : m_shape(new sf::CircleShape(radius)), m_is_colliding(false)
{
}

ShapeNode::ShapeNode(std::vector<sf::Vector2f>& vertices) : m_is_colliding(false)
{
	sf::ConvexShape* polygon = new sf::ConvexShape(vertices.size());

	for (auto i = 0; i < vertices.size(); i++)
	{
		polygon->setPoint(i, vertices[i]);
	}

	m_shape.reset(std::move(polygon));
}

ShapeNode::~ShapeNode() = default;

void ShapeNode::SetColor(sf::Color color)
{
	m_shape->setOutlineColor(color);
	m_shape->setFillColor(color);
}

void ShapeNode::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*m_shape, states);
}

void ShapeNode::UpdateCurrent(sf::Time dt, CommandQueue& commands)
{
	if (m_is_colliding)
	{
		SetColor(sf::Color::Green);
		m_is_colliding = false;
	}
	else
	{
		SetColor(sf::Color::White);
	}
}

void ShapeNode::OnCollision(Collider& other)
{
	m_is_colliding = true;
}
