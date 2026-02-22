/*
* Petr Sulc - GD4b - D00261476
*/

#pragma once
#include "pawn.hpp"
#include "physics.hpp"
#include "physics_body.hpp"
#include "e_pickup_id.hpp"

class Paddle : public Pawn
{
public:
	Paddle(Physics* physics);
	void ApplyMove(float x, float y) override;
	void SetPickup(PickupID pickup_id); // Jakub Polacek - GD4b - D00260171
	void UsePickup() override; // Jakub Polacek - GD4b - D00260171

private:
	virtual void UpdateCurrent(sf::Time dt, CommandQueue& commands) override;
	virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void OnCollision(Collider& other) override;

private:
	sf::Vector2f m_move_vector;
	PhysicsBody m_physics_body;
	PickupID m_pickup_id;
};

