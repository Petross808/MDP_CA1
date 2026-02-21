/*
* Petr Sulc - GD4b - D00261476
* Jakub Polacek - GD4b - D00260171
*/

#include "player_controller.hpp"
#include "pawn.hpp"

PlayerController::PlayerController(ReceiverCategories pawn_category) :
    m_pawn_category(pawn_category),
    m_action_array
    {
        Action("Move Up", true, sf::Keyboard::Scancode::W,
            Command(DerivedAction<Pawn>([](Pawn& p, sf::Time dt) { p.ApplyMove(0, -1); }), m_pawn_category)),
        Action("Move Down", true, sf::Keyboard::Scancode::S,
            Command(DerivedAction<Pawn>([](Pawn& p, sf::Time dt) { p.ApplyMove(0, 1); }), m_pawn_category)),
        Action("Move Left", true, sf::Keyboard::Scancode::A,
            Command(DerivedAction<Pawn>([](Pawn& p, sf::Time dt) { p.ApplyMove(-1, 0); }), m_pawn_category)),
        Action("Move Right", true, sf::Keyboard::Scancode::D,
            Command(DerivedAction<Pawn>([](Pawn& p, sf::Time dt) { p.ApplyMove(1, 0); }), m_pawn_category))
    }
{
}

void PlayerController::HandleEvent(const sf::Event& event, CommandQueue& command_queue)
{
    const auto* key_pressed = event.getIf<sf::Event::KeyPressed>();

    if (!key_pressed) return;

    for (const Action& action : m_action_array)
    {
        if (action.GetKeyBind() == key_pressed->scancode && !action.IsRealTime())
        {
            command_queue.Push(action.GetCommand());
        }
    }
}

void PlayerController::HandleRealTimeInput(CommandQueue& command_queue)
{
    for (const Action& action : m_action_array)
    {
        if (sf::Keyboard::isKeyPressed(action.GetKeyBind()) && action.IsRealTime())
        {
            command_queue.Push(action.GetCommand());
        }
    }
}

Action* PlayerController::GetActionArray()
{
    return m_action_array;
}

const Action* PlayerController::GetActionArray() const
{
    return m_action_array;
}
