/*
* Jakub Polacek - GD4b - D00260171
*/

#include "level.hpp"
#include "paddle.hpp"
#include "wall.hpp"
#include "ball.hpp"

void Level::CreateBounds(SceneNode* root, Physics* physics, sf::FloatRect world_bounds, float wall_width)
{

	std::unique_ptr<Wall> wall1(new Wall(0, 0, world_bounds.size.x, wall_width, physics));
	std::unique_ptr<Wall> wall2(new Wall(0, world_bounds.size.y - wall_width, world_bounds.size.x, wall_width, physics));
	std::unique_ptr<Wall> wall3(new Wall(0, 0, wall_width, world_bounds.size.y, physics));
	std::unique_ptr<Wall> wall4(new Wall(world_bounds.size.x - wall_width, 0, wall_width, world_bounds.size.y, physics));

	root->AttachChild(std::move(wall1));
	root->AttachChild(std::move(wall2));
	root->AttachChild(std::move(wall3));
	root->AttachChild(std::move(wall4));
}


void Level::CreateClassic(SceneNode* root, Physics* physics)
{
	std::unique_ptr<Paddle> paddle(new Paddle(physics));
	root->AttachChild(std::move(paddle));

	

	std::unique_ptr<Wall> rectWall(new Wall(500, 350, 80, 80, physics));
	root->AttachChild(std::move(rectWall));

	std::unique_ptr<Wall> circleWall(new Wall(700, 350, 50, physics));
	root->AttachChild(std::move(circleWall));


	std::vector<sf::Vector2f> triangle{ {-30, 0},{30, 0},{0, 60} };
	std::unique_ptr<Wall> triWall(new Wall(500, 550, triangle, physics));
	root->AttachChild(std::move(triWall));

	std::unique_ptr<Ball> ball(new Ball(400, 300, 20, physics));
	root->AttachChild(std::move(ball));

}
