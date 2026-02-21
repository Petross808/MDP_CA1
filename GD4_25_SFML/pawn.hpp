/*
* Petr Sulc - GD4b - D00261476
* Jakub Polacek - GD4b - D00260171
*/

#include "scene_node.hpp"

class Pawn : public SceneNode
{
public:
	Pawn();
	virtual void ApplyMove(float x, float y) = 0;
};