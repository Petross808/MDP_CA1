/*
* Petr Sulc - GD4b - D00261476
*/

#pragma once
enum CollisionLayer
{
	kDefault = 1 << 0,
	kWall = 1 << 1,
	kPlayer = 1 << 2,
	kBall = 1 << 3,
};