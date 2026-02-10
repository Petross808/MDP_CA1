#pragma once
#include "State.hpp"
#include "world.hpp"

class GameState : public State
{
public:
	GameState(StateStack& stack);
	virtual bool Update(sf::Time delta_time) override;
	virtual void Draw() override;
	virtual bool HandleEvent(const sf::Event& event) override;

private:
	World m_world;
	Player& m_player;
};

