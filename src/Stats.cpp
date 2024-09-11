#include "Stats.h"
#include"Controller.h"
#include <ResourceManager.h>
#include "consts.h"
#include <iostream>


Stats::Stats(Mouse& mouse, Controller& controller):m_stats(5)
{
	this->getStats(mouse, controller);
	sf::Color green = sf::Color(101, 171, 63);
	m_background.setFillColor(green);
	m_background.setSize(sf::Vector2f(1280, 200));
	m_background.setPosition(sf::Vector2f(0, 480));
	
	m_timeText.setCharacterSize(32);
	m_timeText.setPosition(120,575);
	m_timeText.setFont(ResourceManager::instance().getFont());
}

void Stats::getStats(Mouse& mouse, Controller& controller)
{
	m_stats[KEYS] = mouse.getKeys();
	m_stats[LIFE] = mouse.getLife();
	m_stats[SCORE] = mouse.getScore();
	m_stats[TIME] = controller.getTime();
	m_stats[LEVEL] = controller.getCurrLevel() + 1;
}

void Stats::draw(sf::RenderWindow& window)
{

	window.draw(m_background);
	m_timeText.setString(timeToString());
	sf::Text lifeText;
	sf::Text timeText;
	sf::Text levelText;
	sf::Text keysText;
	sf::Text scoreText;
	sf::Text currLevelText;
	sf::Text currScoreText;
	makeText(timeText, 110, 500, "Time");
	makeText(lifeText, 356, 500, "Life");
	makeText(keysText, 592, 500, "Keys");
	makeText(levelText, 828, 500, "Level");
	makeText(scoreText, 1074, 500, "Score");
	makeText(currLevelText, 876, 550, std::to_string(m_stats[LEVEL]));
	makeText(currScoreText, 1122, 550, std::to_string(m_stats[SCORE]));


	window.draw(timeText);
	window.draw(lifeText);
	window.draw(keysText);
	window.draw(scoreText);
	window.draw(m_timeText);
	window.draw(levelText);
	window.draw(currLevelText);
	window.draw(currScoreText);


	printStats(window, LIFE_TEXTURE, 356, 580, LIFE);
	printStats(window, KEY_TEXTURE, 592, 580, KEYS);
	//while(m_stats[SCORE])
}

void Stats::printStats(sf::RenderWindow& window, const std::string texture, int row, int col, int type)
{
	for (int i = 0; i < m_stats[type]; i++)
	{
		sf::Sprite sprite;
		sprite.setTexture(ResourceManager::instance().getTexture(texture));
		sprite.setPosition(sf::Vector2f(row + (TEXTURESIZE * i), col));
		window.draw(sprite);
	}
}

std::string Stats::timeToString()
{
	
	std::string secondsString;
	int seconds = m_stats[TIME] % 60;
	int minutes = m_stats[TIME] / 60;
	std::string minutesString = "0" + std::to_string(minutes);
	secondsString = seconds <= 9 ? "0" + std::to_string(seconds) : std::to_string(seconds);
	std::string time = minutesString + ":" + secondsString;

	return time;
}

void Stats::makeText(sf::Text& text, int row, int col, std::string name)
{
	text.setCharacterSize(FONTSINZE);
	text.setPosition(row, col);
	text.setFont(ResourceManager::instance().getFont());
	text.setString(name);
}
