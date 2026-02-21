/*
* Petr Sulc - GD4b - D00261476
* Jakub Polacek - GD4b - D00260171
*/

#pragma once
#include "scene_node.hpp"

class SpriteNode : public SceneNode
{
public:
	explicit SpriteNode(const sf::Texture& texture);
	SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);

private:
	virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite m_sprite;
	
};

