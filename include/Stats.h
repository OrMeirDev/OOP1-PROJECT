#pragma once
#include "GameObjects/Mouse.h"
#include <string>

class Controller;
class Mouse;
class Stats {
public:
	Stats(Mouse& mouse, Controller& controller);
	void draw(sf::RenderWindow& window);
	void getStats(Mouse& mouse, Controller& controller);
	

private:
	void printStats(sf::RenderWindow& window, const std::string texture, int row, int col, int type);
	std::string timeToString();
	void makeText(sf::Text&, int, int, std::string);

	std::vector <int> m_stats;
	sf::Sprite m_statsBar;
	sf::RectangleShape m_background;

	sf::Text m_timeText;
};