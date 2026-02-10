#include "settings_state.hpp"
#include "Utility.hpp"

SettingsState::SettingsState(StateStack& stack)
    : State(stack)
    , m_gui_container()
    , m_background_sprite(GetContext().textures->Get(TextureID::kTitleScreen))
{
    AddButtonLabel(Action::kMoveUp, 150.f, "Move Up", GetContext());
    AddButtonLabel(Action::kMoveDown, 200.f, "Move Down", GetContext());
    AddButtonLabel(Action::kMoveRight, 250.f, "Move Right", GetContext());
    AddButtonLabel(Action::kMoveLeft, 300.f, "Move Left", GetContext());
    AddButtonLabel(Action::kBulletFire, 350.f, "Fire", GetContext());
    AddButtonLabel(Action::kMissileFire, 400.f, "Missile Fire", GetContext());

    UpdateLabels();

	auto back_button = std::make_shared<gui::Button>(GetContext());
    back_button->setPosition(sf::Vector2f(80.f, 475.f));
    back_button->SetText("Back");
    back_button->SetCallback(std::bind(&SettingsState::RequestStackPop, this));
    m_gui_container.Pack(back_button);
}

void SettingsState::Draw()
{
    sf::RenderWindow& window = *GetContext().window;
    window.draw(m_background_sprite);
    window.draw(m_gui_container);
}

bool SettingsState::Update(sf::Time dt)
{
    return true;
}

bool SettingsState::HandleEvent(const sf::Event& event)
{
    bool is_key_binding = false;

    //Iterate through all of the key binding buttons to see if they are being pressed, waiting for input from the user
    for (std::size_t action = 0; action < static_cast<int>(Action::kActionCount); ++action)
    {
        if (m_binding_buttons[action]->IsActive())
        {
            is_key_binding = true;
            const auto* key_released = event.getIf<sf::Event::KeyReleased>();
            if (key_released)
            {
                GetContext().player->AssignKey(static_cast<Action>(action), key_released->scancode);
                m_binding_buttons[action]->Deactivate();
            }
            break;
        }
    }

    if (is_key_binding)
    {
        UpdateLabels();
    }
    else
    {
        m_gui_container.HandleEvent(event);
    }
    return false;
}

void SettingsState::UpdateLabels()
{
    Player& player = *GetContext().player;
    for (std::size_t i = 0; i < static_cast<int>(Action::kActionCount); ++i)
    {
        sf::Keyboard::Scancode key = player.GetAssignedKey(static_cast<Action>(i));
        m_binding_labels[i]->SetText(Utility::toString(key));
    }
}

void SettingsState::AddButtonLabel(Action action, float y, const std::string& text, StateStack::Context context)
{
    m_binding_buttons[static_cast<int>(action)] = std::make_shared<gui::Button>(context);
    m_binding_buttons[static_cast<int>(action)]->setPosition(sf::Vector2f(80.f, y));
    m_binding_buttons[static_cast<int>(action)]->SetText(text);
    m_binding_buttons[static_cast<int>(action)]->SetToggle(true);

    m_binding_labels[static_cast<int>(action)] = std::make_shared<gui::Label>("",  * context.fonts);
    m_binding_labels[static_cast<int>(action)]->setPosition(sf::Vector2f(300.f, y + 15.f));

    m_gui_container.Pack(m_binding_buttons[static_cast<int>(action)]);
    m_gui_container.Pack(m_binding_labels[static_cast<int>(action)]);
}
