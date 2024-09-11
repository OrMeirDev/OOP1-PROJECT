#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Level.h"
#include <string>
#include "GameObjects/Mouse.h"
#include "Stats.h"
#include "GameObjects/Cat.h"
#include <SFML/Audio.hpp>

class Stats;
class Menu;

class Controller {
public:
	Controller(Menu& menu);
	void run();
	void handleInput(sf::Event);
	void update(sf::Time timer);
	void draw(sf::RenderWindow& window);
	void updateLevel();
	int getCurrLevel() const;
	int getTime() const;
	void addTime();
	void killCat();
	void freezeCats();
	void playSound(std::string soundName);
	void resetAllCats();
	void gameOver();
	void resetAllData();

	void setMouse(sf::Sprite sprite);
	void addCat(sf::Sprite sprite);
private:
	void initLevels();
	Level m_level;
	std::vector<std::string> m_levels;
	std::vector <Cat> m_cats;
	Mouse m_mouse;
	Stats m_stats;
	int m_levelTime;
	int m_currentLevel;
	bool m_isCatsFreeze;

	Menu& m_menu;

	sf::Time m_catsFreezeTimer;

	sf::Sound m_sound;
};