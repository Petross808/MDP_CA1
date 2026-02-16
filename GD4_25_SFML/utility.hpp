/*
* Petr Sulc - GD4b - D00261476
* Jakub Polacek - GD4b - D00260171
*/

#pragma once
#include <SFML/Graphics.hpp>

#include "animation.hpp"

class Utility
{
public:
	static sf::Vector2f Normalise(const sf::Vector2f& source);
	static void CentreOrigin(sf::Sprite& sprite);
	static void CentreOrigin(sf::Text& text);
	static void CentreOrigin(Animation& animation);
	static std::string toString(sf::Keyboard::Scancode key);
	static double toRadians(double degrees);
	static double ToDegrees(double angle);
	static int RandomInt(int exclusive_max);
	static float Length(sf::Vector2f vector);
};

