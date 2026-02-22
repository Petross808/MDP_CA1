/*
* Jakub Polacek - GD4b - D00260171
*/

#include "level.hpp"
#include "paddle.hpp"
#include "wall.hpp"
#include "ball.hpp"
#include "pickup_spawner.hpp"
#include "shape_node.hpp"
#include "player_barrier.hpp"
#include "goal.hpp"

void Level::CreateBounds(SceneNode* root, Physics* physics, sf::FloatRect world_bounds, float wall_width, sf::Texture* texture)
{

	std::unique_ptr<Wall> wall1(new Wall(0, 0, world_bounds.size.x, wall_width, physics, texture));
	std::unique_ptr<Wall> wall2(new Wall(0, world_bounds.size.y - wall_width, world_bounds.size.x, wall_width, physics, texture));
	std::unique_ptr<Wall> wall3(new Wall(0, 0, wall_width, world_bounds.size.y, physics, texture));
	std::unique_ptr<Wall> wall4(new Wall(world_bounds.size.x - wall_width, 0, wall_width, world_bounds.size.y, physics, texture));

	root->AttachChild(std::move(wall1));
	root->AttachChild(std::move(wall2));
	root->AttachChild(std::move(wall3));
	root->AttachChild(std::move(wall4));
}


void Level::CreateClassic(SceneNode* root, Physics* physics, TextureHolder* texture_holder, sf::FloatRect world_bounds, SoundPlayer& sounds)
{
	sf::Texture* wallGrey = &texture_holder->Get(TextureID::kWallGrey);
	sf::Texture* wallRed = &texture_holder->Get(TextureID::kWallRed);
	sf::Texture* stoneWhite = &texture_holder->Get(TextureID::kStoneWhite);
	sf::Texture* stoneGrey = &texture_holder->Get(TextureID::kStoneGrey);

	std::unique_ptr<SceneNode> background(new SceneNode());
	std::unique_ptr<SceneNode> walls(new SceneNode());
	std::unique_ptr<SceneNode> dynamic(new SceneNode());

	CreateBounds(&*walls, physics, world_bounds, 20, wallRed);

	sf::Vector2f center(world_bounds.getCenter());

	std::unique_ptr<Ball> ball(new Ball(center.x - 20, center.y - 20, 20, physics, stoneWhite));
	dynamic->AttachChild(std::move(ball));


	std::unique_ptr<Paddle> paddle_one(new Paddle(0, 200, center.y, physics, sounds));
	dynamic->AttachChild(std::move(paddle_one));

	std::unique_ptr<Paddle> paddle_two(new Paddle(1, world_bounds.size.x - 200, center.y, physics, sounds));
	dynamic->AttachChild(std::move(paddle_two));


	std::unique_ptr<PickupSpawner> pickupSpawner(new PickupSpawner(450, 20, 640, 800, physics, texture_holder, 5));
	dynamic->AttachChild(std::move(pickupSpawner));


	std::unique_ptr<ShapeNode> player_one_zone(new ShapeNode(400, world_bounds.size.y));
	player_one_zone->setPosition({0,0});
	player_one_zone->SetTexture(*stoneGrey);
	background->AttachChild(std::move(player_one_zone));

	std::unique_ptr<ShapeNode> player_two_zone(new ShapeNode(400, world_bounds.size.y));
	player_two_zone->setPosition({ world_bounds.size.x - 400, 0 });
	player_two_zone->SetTexture(*stoneGrey);
	background->AttachChild(std::move(player_two_zone));

	std::unique_ptr<PlayerBarrier> player_one_barrier(new PlayerBarrier(400, 0, 50, world_bounds.size.y, physics));
	background->AttachChild(std::move(player_one_barrier));

	std::unique_ptr<PlayerBarrier> player_two_barrier(new PlayerBarrier(world_bounds.size.x - 450, 0, 50, world_bounds.size.y, physics));
	background->AttachChild(std::move(player_two_barrier));

	std::unique_ptr<Goal> player_one_goal(new Goal(0, 0, 50, world_bounds.size.y, physics));
	background->AttachChild(std::move(player_one_goal));

	std::unique_ptr<Goal> player_two_goal(new Goal(world_bounds.size.x - 50, 0, 50, world_bounds.size.y, physics));
	background->AttachChild(std::move(player_two_goal));

	root->AttachChild(std::move(background));
	root->AttachChild(std::move(walls));
	root->AttachChild(std::move(dynamic));
}
