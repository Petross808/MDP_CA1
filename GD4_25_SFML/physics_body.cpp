/*
* Petr Sulc - GD4b - D00261476
*/

#include "physics_body.hpp"

#include <iostream>

PhysicsBody::PhysicsBody(SceneNode* controlled, Physics* physics, float mass, float maxSpeed, float drag, float elasticity, float grip) :
	m_controlled_object(controlled),
	m_physics(physics),
	m_mass(mass),
	m_max_speed(maxSpeed),
	m_linear_drag(drag),
	m_velocity(),
	m_acceleration(),
	m_elasticity(elasticity),
	m_kinematic(false),
	m_grip(grip)
{
	m_physics->Register(this);
}

PhysicsBody::~PhysicsBody()
{
	m_physics->Unregister(this);
}

void PhysicsBody::AddForce(float x, float y)
{
	m_acceleration.x += x;
	m_acceleration.y += y;
}

void PhysicsBody::ApplyImpulse(float strength, sf::Vector2f normal)
{
	m_velocity += (strength / m_mass) * normal;
}

void PhysicsBody::Move(sf::Vector2f delta)
{
	m_controlled_object->move(delta);
}

void PhysicsBody::Simulate(sf::Time dt)
{
	float dts = dt.asSeconds();
	m_velocity += m_acceleration * dts;
	m_velocity -= m_velocity * m_linear_drag * dts;
	
	if (m_velocity.lengthSquared() > m_max_speed * m_max_speed)
	{
		m_velocity = m_velocity.normalized() * m_max_speed;
	}
	
	Move(m_velocity * dts);

	m_acceleration = { 0,0 };
}

sf::Vector2f PhysicsBody::GetVelocity() const
{
	return m_velocity;
}

float PhysicsBody::GetMass() const
{
	return m_mass;
}

float PhysicsBody::GetElasticity() const
{
	return m_elasticity;
}

float PhysicsBody::GetGrip() const
{
	return m_grip;
}

void PhysicsBody::SetAsKinematic()
{
	m_kinematic = true;
}

bool PhysicsBody::IsKinematic() const
{
	return m_kinematic;
}