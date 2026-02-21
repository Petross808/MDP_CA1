/*
* Petr Sulc - GD4b - D00261476
* Jakub Polacek - GD4b - D00260171
*/

#include "world.hpp"
#include "sound_node.hpp"
#include "paddle.hpp"
#include "wall.hpp"

World::World(sf::RenderTarget& output_target, FontHolder& font, SoundPlayer& sounds)
	: m_target(output_target)
	, m_camera(output_target.getDefaultView())
	, m_textures()
	, m_fonts(font)
	, m_sounds(sounds)
	, m_scene_graph(ReceiverCategories::kScene)
	, m_world_bounds(sf::Vector2f(0.f, 0.f), sf::Vector2f(m_camera.getSize().x, m_camera.getSize().y))
{
	static_cast<void>(m_scene_texture.resize({ m_target.getSize().x, m_target.getSize().y }));
	LoadTextures();
	BuildScene();
}

void World::Update(sf::Time dt)
{
	UpdateSounds();

	//Process commands from the scenegraph
	while (!m_command_queue.IsEmpty())
	{
		m_scene_graph.OnCommand(m_command_queue.Pop(), dt);
	}
	
	m_scene_graph.RemoveWrecks();
	m_scene_graph.Update(dt, m_command_queue);

	HandleCollisions();
}

void World::Draw()
{
	m_target.setView(m_camera);
	m_target.draw(m_scene_graph);
}

CommandQueue& World::GetCommandQueue()
{
	return m_command_queue;
}

void World::LoadTextures()
{
}

void World::BuildScene()
{
	std::unique_ptr<SoundNode> soundNode(new SoundNode(m_sounds));
	m_scene_graph.AttachChild(std::move(soundNode));

	std::unique_ptr<Paddle> paddle(new Paddle(&m_physics));
	m_scene_graph.AttachChild(std::move(paddle));

	float wall_width = 20;
	std::unique_ptr<Wall> wall1(new Wall(0, 0, m_world_bounds.size.x, wall_width, &m_physics));
	std::unique_ptr<Wall> wall2(new Wall(0, m_world_bounds.size.y - wall_width, m_world_bounds.size.x, wall_width, &m_physics));
	std::unique_ptr<Wall> wall3(new Wall(0, 0, wall_width, m_world_bounds.size.y, &m_physics));
	std::unique_ptr<Wall> wall4(new Wall(m_world_bounds.size.x - wall_width, 0, wall_width, m_world_bounds.size.y, &m_physics));

	m_scene_graph.AttachChild(std::move(wall1));
	m_scene_graph.AttachChild(std::move(wall2));
	m_scene_graph.AttachChild(std::move(wall3));
	m_scene_graph.AttachChild(std::move(wall4));

	std::unique_ptr<Wall> rectWall(new Wall(500, 350, 80, 80, &m_physics));
	m_scene_graph.AttachChild(std::move(rectWall));

	std::unique_ptr<Wall> circleWall(new Wall(700, 350, 50, &m_physics));
	m_scene_graph.AttachChild(std::move(circleWall));


	std::vector<sf::Vector2f> triangle{ {-30, 0},{30, 0},{0, 60} };
	std::unique_ptr<Wall> triWall(new Wall(500, 550, triangle, &m_physics));
	m_scene_graph.AttachChild(std::move(triWall));

}

sf::FloatRect World::GetViewBounds() const
{
	return sf::FloatRect(m_camera.getCenter() - m_camera.getSize() / 2.f, m_camera.getSize());;
}

void World::HandleCollisions()
{
	std::vector<Physics::Pair> results;
	m_physics.EvaluateAll(results);

	for (auto& collision : results)
	{
		collision.first->EvaluateCollision(*collision.second);
		collision.second->EvaluateCollision(*collision.first);
	}
}

void World::UpdateSounds()
{
	sf::Vector2f listener_position;

	listener_position = m_camera.getCenter();

	m_sounds.SetListenerPosition(listener_position);

	m_sounds.RemoveStoppedSounds();
}