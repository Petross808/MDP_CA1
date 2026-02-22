/*
* Jakub Polacek - GD4b - D00260171
*/

#include "level.hpp"
#include "paddle.hpp"
#include "wall.hpp"
#include "ball.hpp"
#include "pickup.hpp"

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


void Level::CreateClassic(SceneNode* root, Physics* physics, TextureHolder* texture_holder)
{
	sf::Texture* wallGrey = &texture_holder->Get(TextureID::kWallGrey);

	std::unique_ptr<SceneNode> background(new SceneNode());
	std::unique_ptr<Wall> rectWall(new Wall(50, 20, 100, 860, physics, wallGrey));
	background->AttachChild(std::move(rectWall));

	std::unique_ptr<Wall> circleWall(new Wall(700, 350, 50, physics, wallGrey));
	background->AttachChild(std::move(circleWall));

	std::vector<sf::Vector2f> triangle{ {-30, 0},{30, 0},{0, 60} };
	std::unique_ptr<Wall> triWall(new Wall(500, 550, triangle, physics, wallGrey));
	background->AttachChild(std::move(triWall));


	root->AttachChild(std::move(background));

	std::unique_ptr<Pickup> speedUp(new Pickup(1000, 500, 100, physics, PickupID::kSpeedBoost));
	root->AttachChild(std::move(speedUp));


	std::unique_ptr<Ball> ball(new Ball(400, 300, 20, physics));
	root->AttachChild(std::move(ball));

	std::unique_ptr<Paddle> paddle(new Paddle(physics));
	root->AttachChild(std::move(paddle));
}
