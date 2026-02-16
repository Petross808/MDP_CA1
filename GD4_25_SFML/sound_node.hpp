/*
* Petr Sulc - GD4b - D00261476
* Jakub Polacek - GD4b - D00260171
*/

#pragma once
#include "scene_node.hpp"
#include "sound_player.hpp"

class SoundNode : public SceneNode
{
public:
	SoundNode(SoundPlayer& player);
	void PlaySound(SoundID sound, sf::Vector2f position);

	virtual unsigned int GetCategory() const override;

private:
	SoundPlayer& m_sounds;
};

