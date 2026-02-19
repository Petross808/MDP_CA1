/*
* Petr Sulc - GD4b - D00261476
*/

#pragma once
#include "collider.hpp"

class PolygonCollider : public Collider
{
private:
	std::vector<sf::Vector2f> m_vertices;

public:
	PolygonCollider(float x, float y, std::vector<sf::Vector2f>& vertices, Physics* physics);

	virtual bool CheckCollision(Collider* other) override;

	virtual bool CollideWith(Collider* other) override;
	virtual bool CollideWith(BoxCollider* other) override;
	virtual bool CollideWith(CircleCollider* other) override;
	virtual bool CollideWith(PolygonCollider* other) override;

	static bool CheckPolygonSAT(
		sf::Vector2f& firstPos, std::vector<sf::Vector2f>& firstVertices,
		sf::Vector2f& secondPos, std::vector<sf::Vector2f>& secondVertices);
	static bool CheckCircleSAT(
		sf::Vector2f& polyPos, std::vector<sf::Vector2f>& polyVertices,
		sf::Vector2f& circlePos, float circleRadius);
};
