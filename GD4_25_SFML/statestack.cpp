#include "statestack.hpp"
#include "state.hpp"

StateStack::PendingChange::PendingChange(std::function<void()> pending_call) : callback(pending_call)
{
}

StateStack::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts,
	Player& player, MusicPlayer& music, SoundPlayer& sound) : 
	window(&window),
	textures(&textures),
	fonts(&fonts),
	player(&player),
	music(&music),
	sound(&sound)
{
}

StateStack::StateStack(Context context) : m_context(context)
{
}

StateStack::~StateStack() = default;

void StateStack::Update(sf::Time dt)
{
	for (auto itr = m_stack.rbegin(); itr != m_stack.rend(); ++itr)
	{
		if (!(*itr)->Update(dt))
		{
			break;
		}
	}
	ApplyPendingChanges();
}

void StateStack::Draw()
{
	for (State::Ptr& state : m_stack)
	{
		state->Draw();
	}

}

void StateStack::HandleEvent(const sf::Event& event)
{
	for (auto itr = m_stack.rbegin(); itr != m_stack.rend(); ++itr)
	{
		if (!(*itr)->HandleEvent(event))
		{
			break;
		}
	}
	ApplyPendingChanges();
}

void StateStack::PopState()
{
	std::function<void()> clear_func = [this]() { m_stack.pop_back(); };

	m_pending_list.emplace_back(PendingChange(clear_func));
}

void StateStack::ClearStack()
{
	std::function<void()> clear_func = [this]() { m_stack.clear(); };

	m_pending_list.emplace_back(PendingChange(clear_func));
}

void StateStack::ApplyPendingChanges()
{
	for (PendingChange change : m_pending_list)
	{
		change.callback();
	}

	m_pending_list.clear();
}

bool StateStack::IsEmpty() const
{
	return m_stack.empty();
}

StateStack::Context StateStack::GetContext() const
{
	return m_context;
}