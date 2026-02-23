#pragma once

class ScoreData
{
public:
	ScoreData();
	~ScoreData();
	int GetTeamOneScore() const;
	int GetTeamTwoScore() const;

	void SetTeamOneScore(int score);
	void SetTeamTwoScore(int score);

	void Reset();

private:
	int m_team_one_score;
	int m_team_two_score;
};

