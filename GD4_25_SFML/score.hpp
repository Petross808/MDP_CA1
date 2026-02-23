#pragma once
#include "scene_node.hpp"
#include "resource_identifiers.hpp"
#include "score_data.hpp"

class Score : public SceneNode
{
public:
	Score(float x, float y, FontHolder& fonts, ScoreData& score);
	~Score();

	void IncrementTeamOne();
	void IncrementTeamTwo();

private:
	void UpdateText();

private:
	ScoreData& m_score;
	sf::Text* m_text;
	int m_team_one;
	int m_team_two;
};

