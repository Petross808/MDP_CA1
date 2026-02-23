#include "score.hpp"
#include "text_node.hpp"

Score::Score(float x, float y, FontHolder& fonts, ScoreData& score) : 
	SceneNode(ReceiverCategories::kScore),
	m_score(score),
	m_team_one(0),
	m_team_two(0)
{
	setPosition({ x, y });
	sf::String initText("0 : 0");
	std::unique_ptr<TextNode> textNode(new TextNode(fonts, initText));
	m_text = &textNode->GetTextRef();
	m_text->setCharacterSize(64);
	m_text->setOrigin(m_text->getLocalBounds().getCenter());
	AttachChild(std::move(textNode));
}

Score::~Score() = default;

void Score::IncrementTeamOne()
{
	++m_team_one;
	m_score.SetTeamOneScore(m_team_one);
	UpdateText();
}

void Score::IncrementTeamTwo()
{
	++m_team_two;
	m_score.SetTeamTwoScore(m_team_two);
	UpdateText();
}

void Score::UpdateText()
{
	sf::String text(std::to_string(m_team_one) + " : " + std::to_string(m_team_two));
	m_text->setString(text);
	m_text->setOrigin(m_text->getLocalBounds().getCenter());
}
