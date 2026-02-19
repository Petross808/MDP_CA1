/*
* Petr Sulc - GD4b - D00261476
*/

#pragma once
#include "pawn.hpp"
#include "physics.hpp"

class Paddle : public Pawn
{
public:
	Paddle(Physics* physics);
	void ApplyMove(float x, float y) override;

private:
	virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void OnCollision(Collider& other) override;
};

