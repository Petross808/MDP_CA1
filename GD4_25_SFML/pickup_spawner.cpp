/*
* Jakub Polacek - GD4b - D00260171
*/

#include "pickup_spawner.hpp"
#include "pickup.hpp"

PickupSpawner::PickupSpawner(float x, float y, Physics* physics_ptr, float spawn_time) :
	m_physics_ptr(physics_ptr),
	m_has_pickup(false),
	m_spawn_time(spawn_time),
	m_cooldown(spawn_time)
{
	setPosition(sf::Vector2f(x, y));
}

PickupSpawner::~PickupSpawner() = default;


void PickupSpawner::UpdateCurrent(sf::Time dt, CommandQueue& commands)
{
	if (m_has_pickup)
	{
		return;
	}
	else if(m_cooldown > 0)
	{
		m_cooldown -= dt.asSeconds();
		return;
	}
	else
	{
		std::unique_ptr<Pickup> pickupTest(new Pickup(0, 0, 50, m_physics_ptr, PickupID::kSpeedBoost));
		this->AttachChild(std::move(pickupTest));
		m_cooldown = m_spawn_time;
		return;
	}
}