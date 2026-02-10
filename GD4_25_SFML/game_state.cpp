#include "game_state.hpp"
#include "mission_status.hpp"
#include "game_over_state.hpp"
#include "pause_state.hpp"

GameState::GameState(StateStack& stack) : State(stack), m_world(*GetContext().window, *GetContext().fonts, *GetContext().sound), m_player(*GetContext().player)
{
	GetContext().music->Play(MusicThemes::kMissionTheme);
}

void GameState::Draw()
{
	m_world.Draw();
}

bool GameState::Update(sf::Time dt)
{
	m_world.Update(dt);

	if (!m_world.HasAlivePlayer())
	{
		m_player.SetMissionStatus(MissionStatus::kMissionFailure);
		RequestStackPush<GameOverState>();
	}
	else if (m_world.HasPlayerReachedEnd())
	{
		m_player.SetMissionStatus(MissionStatus::kMissionSuccess);
		RequestStackPush<GameOverState>();
	}

	CommandQueue& commands = m_world.GetCommandQueue();
	m_player.HandleRealTimeInput(commands);
	return true;
}

bool GameState::HandleEvent(const sf::Event& event)
{
	CommandQueue& commands = m_world.GetCommandQueue();
	m_player.HandleEvent(event, commands);

	//Escape should bring up the pause menu
	const auto* keypress = event.getIf<sf::Event::KeyPressed>();
	if(keypress && keypress->scancode == sf::Keyboard::Scancode::Escape)
	{
		RequestStackPush<PauseState>();
	}
	return true;
}


