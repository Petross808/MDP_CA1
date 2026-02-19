/*
* Petr Sulc - GD4b - D00261476
*/

#pragma once
#include <vector>

#include "collider.hpp"

class Collider;

class Physics
{
public:
	typedef std::pair<Collider*, Collider*> Pair;
private:
	std::vector<Collider*> m_dynamic_object_vector;
	std::vector<Collider*> m_static_object_vector;

private:
	void CheckCollision(Collider* first, Collider* second, std::vector<Pair>& collisions);
public:
	void Register(Collider* shape);
	void Unregister(Collider* shape);
	void EvaluateAll(std::vector<Pair>& result);
};