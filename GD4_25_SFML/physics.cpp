/*
* Petr Sulc - GD4b - D00261476
*/

#include "physics.hpp"

void Physics::CheckCollision(Collider* first, Collider* second, std::vector<Pair>& collisions)
{
	if (first->BoundingBoxOverlap(second))
	{
		if (first->CheckCollision(second))
		{
			collisions.emplace_back(Pair(first, second));
		}
	}
}

void Physics::Register(Collider* shape)
{
	m_object_vector.emplace_back(shape);
}

void Physics::Unregister(Collider* shape)
{
	auto size = m_object_vector.size();
	for (int i = 0; i < size; i++)
	{
		if (shape == m_object_vector[i])
		{
			std::swap(m_object_vector[i],m_object_vector[size - 1]);
			m_object_vector.pop_back();
			return;
		}
	}
}

void Physics::EvaluateAll(std::vector<Pair>& result)
{
	std::vector<Collider*>::iterator inner;
	for (std::vector<Collider*>::iterator iter = m_object_vector.begin(); iter != m_object_vector.end(); iter++)
	{
		for (++(inner = iter); inner != m_object_vector.end(); ++inner)
		{
			CheckCollision(*iter, *inner, result);
		}
	}
}
