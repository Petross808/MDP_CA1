#include "score_data.hpp"

ScoreData::ScoreData() : 
	m_team_one_score(0),
	m_team_two_score(0)
{
}

ScoreData::~ScoreData() = default;

int ScoreData::GetTeamOneScore() const
{
	return m_team_one_score;
}

int ScoreData::GetTeamTwoScore() const
{
	return m_team_two_score;
}

void ScoreData::SetTeamOneScore(int score)
{
	m_team_one_score = score;
}

void ScoreData::SetTeamTwoScore(int score)
{
	m_team_two_score = score;
}

void ScoreData::Reset()
{
	m_team_one_score = 0;
	m_team_two_score = 0;
}