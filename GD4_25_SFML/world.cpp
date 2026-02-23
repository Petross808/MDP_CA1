/*
* Petr Sulc - GD4b - D00261476
* Jakub Polacek - GD4b - D00260171
*/

#include "world.hpp"
#include "level.hpp"
#include "sound_node.hpp"
#include "score.hpp"

World::World(sf::RenderTarget& output_target, FontHolder& font, SoundPlayer& sounds, ScoreData& score)
	: m_target(output_target)
	, m_camera(output_target.getDefaultView())
	, m_textures()
	, m_fonts(font)
	, m_sounds(sounds)
	, m_scene_graph(ReceiverCategories::kScene)
	, m_world_bounds(sf::Vector2f(0.f, 0.f), sf::Vector2f(m_camera.getSize().x, m_camera.getSize().y))
	, m_physics()
	, m_score(score)
{
	static_cast<void>(m_scene_texture.resize({ m_target.getSize().x, m_target.getSize().y }));
	LoadTextures();
	BuildScene();
}

void World::Update(sf::Time dt)
{
	UpdateSounds();

	m_physics.SimulateAllBodies(dt);
	HandleCollisions();

	//Process commands from the scenegraph
	while (!m_command_queue.IsEmpty())
	{
		m_scene_graph.OnCommand(m_command_queue.Pop(), dt);
	}
	
	m_scene_graph.RemoveWrecks();
	m_scene_graph.Update(dt, m_command_queue);
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
	m_textures.Load(TextureID::kWallGrey, "Media/Textures/t_wall_grey.png");
	m_textures.Load(TextureID::kWallRed, "Media/Textures/t_wall_red.png");
	m_textures.Load(TextureID::kStoneWhite, "Media/Textures/t_flat_stone_white.png");
	m_textures.Load(TextureID::kStoneGrey, "Media/Textures/t_flat_stone_grey.png");
	m_textures.Load(TextureID::kStoneBlack, "Media/Textures/t_flat_stone_black.png");
	m_textures.Get(TextureID::kWallGrey).setRepeated(true);
	m_textures.Get(TextureID::kWallRed).setRepeated(true);
	m_textures.Get(TextureID::kStoneWhite).setRepeated(true);
	m_textures.Get(TextureID::kStoneGrey).setRepeated(true);
	m_textures.Get(TextureID::kStoneBlack).setRepeated(true);
}

void World::BuildScene()
{
	std::unique_ptr<SoundNode> soundNode(new SoundNode(m_sounds));
	m_scene_graph.AttachChild(std::move(soundNode));

	Level::CreateClassic(&m_scene_graph, &m_physics, &m_textures, m_world_bounds);

	std::unique_ptr<Score> score(new Score(m_world_bounds.getCenter().x, m_world_bounds.getCenter().y + 100, m_fonts, m_score));
	m_scene_graph.AttachChild(std::move(score));	
}

sf::FloatRect World::GetViewBounds() const
{
	return sf::FloatRect(m_camera.getCenter() - m_camera.getSize() / 2.f, m_camera.getSize());;
}

void World::HandleCollisions()
{
	std::vector<Physics::Pair> results;
	m_physics.EvaluateAllCollisions(results);

	for (auto& collision : results)
	{
		collision.first->EvaluateCollision(*collision.second, m_command_queue);
		collision.second->EvaluateCollision(*collision.first, m_command_queue);
	}
}

void World::UpdateSounds()
{
	sf::Vector2f listener_position;

	listener_position = m_camera.getCenter();

	m_sounds.SetListenerPosition(listener_position);

	m_sounds.RemoveStoppedSounds();
}