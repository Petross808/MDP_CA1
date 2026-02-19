/*
* Petr Sulc - GD4b - D00261476
*/

#include "box_collider.hpp"
#include "circle_collider.hpp"
#include "polygon_collider.hpp"
#include "utility.hpp"


PolygonCollider::PolygonCollider(float x, float y, std::vector<sf::Vector2f>& vertices, Physics* physics, bool dynamic) :
	Collider(x, y, physics, dynamic),
	m_vertices(vertices)
{
	sf::Vector2f min(m_vertices[0]);
	sf::Vector2f max(m_vertices[0]);


	for (auto& vertex : m_vertices)
	{
		min.x = std::min(min.x, vertex.x);
		min.y = std::min(min.y, vertex.y);
		max.x = std::max(max.x, vertex.x);
		max.y = std::max(max.y, vertex.y);
	}

	for (auto& vertex : m_vertices)
	{
		vertex -= min;
	}

	m_box_size = max - min;
	move(min);
}

bool PolygonCollider::CheckCollision(Collider* other)
{
	return other->CollideWith(this);
}

bool PolygonCollider::CollideWith(Collider* other)
{
	return true;
}

bool PolygonCollider::CollideWith(BoxCollider* other)
{
	sf::Vector2f firstPos(this->GetWorldPosition());
	sf::Vector2f secondPos(other->GetWorldPosition());

	sf::Vector2f boxSize(other->GetBoxSize());
	std::vector<sf::Vector2f> boxVertices
	{
		{0, 0},
		{boxSize.x, 0},
		boxSize,
		{0, boxSize.y}
	};

	if (!CheckPolygonSAT(firstPos, this->m_vertices, secondPos, boxVertices))
	{
		return false;
	}
	else if (!CheckPolygonSAT(secondPos, boxVertices, firstPos, this->m_vertices))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool PolygonCollider::CollideWith(CircleCollider* other)
{
	sf::Vector2f polyPos(this->GetWorldPosition());
	sf::Vector2f circlePos(other->GetCenter());

	return CheckCircleSAT(polyPos, m_vertices, circlePos, other->GetRadius());
}

bool PolygonCollider::CollideWith(PolygonCollider* other)
{
	sf::Vector2f firstPos(this->GetWorldPosition());
	sf::Vector2f secondPos(other->GetWorldPosition());

	if (!CheckPolygonSAT(firstPos, this->m_vertices, secondPos, other->m_vertices))
	{
		return false;
	}
	else if (!CheckPolygonSAT(secondPos, other->m_vertices, firstPos, this->m_vertices))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool PolygonCollider::CheckPolygonSAT(
	sf::Vector2f& firstPos,
	std::vector<sf::Vector2f>& firstVertices,
	sf::Vector2f& secondPos,
	std::vector<sf::Vector2f>& secondVertices)
{
	for (size_t i = 0; i < firstVertices.size(); i++)
	{
		sf::Vector2f lineStart(firstVertices[i % firstVertices.size()]);
		sf::Vector2f lineEnd(firstVertices[(i + 1) % firstVertices.size()]);

		sf::Vector2 normal(-(lineEnd.y - lineStart.y), lineEnd.x - lineStart.x);
		normal = normal.normalized();

		float dot1 = Utility::DotProduct(normal, firstVertices[0]);
		float min1 = dot1;
		float max1 = dot1;

		for (auto& vertex : firstVertices)
		{
			dot1 = Utility::DotProduct(normal, vertex);
			min1 = std::min(min1, dot1);
			max1 = std::max(max1, dot1);
		}

		float dot2 = Utility::DotProduct(normal, secondVertices[0]);
		float min2 = dot2;
		float max2 = dot2;
		for (auto& vertex : secondVertices)
		{
			dot2 = Utility::DotProduct(normal, vertex);
			min2 = std::min(min2, dot2);
			max2 = std::max(max2, dot2);
		}

		float offset = Utility::DotProduct(normal, firstPos - secondPos);

		min1 += offset;
		max1 += offset;

		if (min1 - max2 > 0 || min2 - max1 > 0)
		{
			return false;
		}
	}

	return true;
}

bool PolygonCollider::CheckCircleSAT(
	sf::Vector2f& polyPos,
	std::vector<sf::Vector2f>& polyVertices,
	sf::Vector2f& circlePos,
	float circleRadius)
{
	for (size_t i = 0; i < polyVertices.size(); i++)
	{
		sf::Vector2f lineStart(polyVertices[i % polyVertices.size()]);
		sf::Vector2f lineEnd(polyVertices[(i + 1) % polyVertices.size()]);

		sf::Vector2 normal(-(lineEnd.y - lineStart.y), lineEnd.x - lineStart.x);
		normal = normal.normalized();

		float dot1 = Utility::DotProduct(normal, polyVertices[0]);
		float min1 = dot1;
		float max1 = dot1;

		for (auto& vertex : polyVertices)
		{
			dot1 = Utility::DotProduct(normal, vertex);
			min1 = std::min(min1, dot1);
			max1 = std::max(max1, dot1);
		}

		float min2 =  -circleRadius;
		float max2 =  circleRadius;

		float offset = Utility::DotProduct(normal, polyPos - circlePos);

		min1 += offset;
		max1 += offset;

		if (min1 - max2 > 0 || min2 - max1 > 0)
		{
			return false;
		}
	}


	sf::Vector2f closest;
	float minDist = FLT_MAX;

	sf::Vector2f vertOffset;
	float dist;
	for (auto& vert : polyVertices)
	{
		vertOffset = polyPos + vert - circlePos;
		dist = Utility::SqrLength(vertOffset);
		if (dist < minDist)
		{
			closest = vertOffset;
			minDist = dist;
		}
	}

	assert(closest != sf::Vector2f());
	sf::Vector2 normal(closest.normalized());

	float dot1 = Utility::DotProduct(normal, polyVertices[0]);
	float min1 = dot1;
	float max1 = dot1;

	for (auto& vertex : polyVertices)
	{
		dot1 = Utility::DotProduct(normal, vertex);
		min1 = std::min(min1, dot1);
		max1 = std::max(max1, dot1);
	}

	float min2 = -circleRadius;
	float max2 = circleRadius;

	float offset = Utility::DotProduct(normal, polyPos - circlePos);

	min1 += offset;
	max1 += offset;

	if (min1 - max2 > 0 || min2 - max1 > 0)
	{
		return false;
	}

	return true;
}