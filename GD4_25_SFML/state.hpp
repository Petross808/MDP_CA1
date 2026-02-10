#pragma once
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "music_player.hpp"
#include "sound_player.hpp"
#include "statestack.hpp"

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	struct Context
	{
		Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player, MusicPlayer& music, SoundPlayer& sound);
		sf::RenderWindow* window;
		TextureHolder* textures;
		FontHolder* fonts;
		Player* player;
		MusicPlayer* music;
		SoundPlayer* sound;
	};

public:
	State(StateStack& stack);
	virtual ~State();
	virtual void Draw() = 0;
	virtual bool Update(sf::Time dt) = 0;
	virtual bool HandleEvent(const sf::Event& event) = 0;

protected:
	template<typename T>
	void RequestStackPush();
	void RequestStackPop();
	void RequestStackClear();

	StateStack::Context GetContext() const;

private:
	StateStack* m_stack;
};

template<typename T>
void State::RequestStackPush()
{
	m_stack->PushState<T>();
}