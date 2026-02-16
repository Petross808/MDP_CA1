/*
* Petr Sulc - GD4b - D00261476
* Jakub Polacek - GD4b - D00260171
*/

#include "application.hpp"
#include "constants.hpp"
#include "e_texture_id.hpp"
#include "e_font_id.hpp"
#include "title_state.hpp"
#include "resource_holder.hpp"

Application::Application() : 
	m_window(sf::VideoMode({ kWindowWidth, kWindowHeight }), kWindowTitle, sf::Style::Close), 
	m_player(ReceiverCategories::kPlayer),
	m_stack(StateStack::Context(m_window, m_textures, m_fonts, m_player, m_music, m_sound))
{
	m_window.setKeyRepeatEnabled(false);

	m_fonts.Load(FontID::kMain, "Media/Fonts/Sansation.ttf");
	m_textures.Load(TextureID::kButton, "Media/Textures/Buttons.png");
	m_textures.Load(TextureID::kTitleScreen, "Media/Textures/TitleScreen.png");

	m_stack.PushState<TitleState>();
}

Application::~Application() = default;

void Application::Run()
{
	sf::Clock clock;
	sf::Time time_since_last_update = sf::Time::Zero;
	while (m_window.isOpen())
	{
		time_since_last_update += clock.restart();
		while (time_since_last_update.asSeconds() > kTimePerFrame)
		{
			time_since_last_update -= sf::seconds(kTimePerFrame);
			ProcessInput();
			Update(sf::seconds(kTimePerFrame));

			if (m_stack.IsEmpty())
			{
				m_window.close();
			}
		}
		Render();
	}
}

void Application::ProcessInput()
{
	while (const std::optional event = m_window.pollEvent())
	{
		m_stack.HandleEvent(*event);

		if (event->is<sf::Event::Closed>())
		{
			m_window.close();
		}

	}
}

void Application::Update(sf::Time dt)
{
	m_stack.Update(dt);
}

void Application::Render()
{
	m_window.clear();
	m_stack.Draw();
	m_window.display();
}

