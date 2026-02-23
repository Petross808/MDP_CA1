/*
* Petr Sulc - GD4b - D00261476
*/

#pragma once
#include "scene_node.hpp"
#include "physics.hpp"

class Physics;

class PhysicsBody
{
public:
	PhysicsBody(SceneNode* controlled, Physics* physics, float mass, float maxSpeed, float drag, float elasticity, float grip = 0);
	~PhysicsBody();

	void AddForce(float x, float y);
	void ApplyImpulse(float strength, sf::Vector2f normal);
	void Move(sf::Vector2f delta);
	void Simulate(sf::Time dt);

	sf::Vector2f GetVelocity() const;
	float GetMass() const;
	float GetElasticity() const;
	float GetGrip() const;

	void SetAsKinematic();
	bool IsKinematic() const;

	void Reset();

private:
	SceneNode* m_controlled_object;
	Physics* m_physics;

	bool m_kinematic;
	float m_mass;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;
	float m_max_speed;
	float m_linear_drag;
	float m_elasticity;
	float m_grip;
};

