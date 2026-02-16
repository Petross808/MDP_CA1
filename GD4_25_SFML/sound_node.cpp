/*
* Petr Sulc - GD4b - D00261476
* Jakub Polacek - GD4b - D00260171
*/

#include "sound_node.hpp"

SoundNode::SoundNode(SoundPlayer& player)
    : m_sounds(player)
{
}

void SoundNode::PlaySound(SoundID sound, sf::Vector2f position)
{
    m_sounds.Play(sound, position);
}

unsigned int SoundNode::GetCategory() const
{
    return static_cast<int>(ReceiverCategories::kSoundEffect);
}
