#include "Controller.h"
#include <SFML/Graphics.hpp>
#include "consts.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <SFML/Audio.hpp>
#include "ResourceManager.h"
#include "Menu.h"

Controller::Controller(Menu& menu):m_currentLevel(0),m_mouse(*this,m_level),m_level(*this) ,m_stats(m_mouse, *this),m_isCatsFreeze(false)
	,m_menu(menu)
{
	initLevels();
	m_catsFreezeTimer = sf::Time::Zero;
}

void Controller::run()
{
	m_level.loadLevel(m_levels[m_currentLevel]);
}

void Controller::handleInput(sf::Event event)
{
	m_mouse.setDirections();
}

void Controller::update(sf::Time timer) 
{
	float dt = timer.asSeconds();
	m_mouse.move(dt);
	m_level.update(m_mouse,timer);
	if (m_level.getTime() == 0) {
		m_cats.clear();
		m_level.loadLevel(m_levels[m_currentLevel]);
		m_mouse.reduceLife();
	}
	
	if (m_isCatsFreeze) {
		if (m_catsFreezeTimer >= sf::seconds(FREEZE_TIMER)) {
			m_catsFreezeTimer = sf::Time::Zero;
			m_isCatsFreeze = false;
		}
		else m_catsFreezeTimer += timer;
	}
	else {
		for (Cat& cat : m_cats) {
			cat.setDirections(m_mouse.getPosition());
			cat.move(dt);
			if (cat.isColided(m_mouse)) {
				cat.handleCollision(m_mouse);
			}
		}
	}
}

void Controller::draw(sf::RenderWindow& window) // draw objects on window 
{
	m_level.draw(window);
	m_mouse.draw(window);
	m_stats.getStats(m_mouse, *this);
	m_stats.draw(window);
	for (Cat& cat : m_cats)
	{
		cat.draw(window);
	}
}

void Controller::updateLevel()
{
	if (m_currentLevel+1 == m_levels.size())
	{
		m_menu.setEndGameOpen(true);
		return;
	}
	m_currentLevel++;
}

int Controller::getCurrLevel() const
{
	return m_currentLevel;
}

int Controller::getTime() const
{
	return m_level.getTime();
}
//----------------------------------------------------------------------------
void Controller::addTime()
{
	m_level.addTime(TIME_VALUE);
}
//----------------------------------------------------------------------------
void Controller::killCat()
{
	if (m_cats.size() > 0) {
		m_cats.pop_back();
	}
}
//----------------------------------------------------------------------------
void Controller::freezeCats()
{
	m_isCatsFreeze = true;
}
//----------------------------------------------------------------------------
void Controller::playSound(std::string soundName)
{
	m_sound.setBuffer(ResourceManager::instance().getSound(soundName));
	m_sound.play();
}
//----------------------------------------------------------------------------
void Controller::resetAllCats()
{
	for (Cat& cat : m_cats) {
		cat.resetPosition();
	}
}
//----------------------------------------------------------------------------
void Controller::gameOver()
{
	m_menu.setGameOver(true);
}
//----------------------------------------------------------------------------
void Controller::resetAllData()
{
	m_cats.clear();
	m_currentLevel = 0;
	m_level.resetAllData();
	m_mouse.resetAllData();
}
//----------------------------------------------------------------------------
void Controller::setMouse(sf::Sprite sprite) 
{
	m_mouse.setSprite(sprite);
	m_mouse.setStartingPosition(sprite.getPosition());
}
//----------------------------------------------------------------------------
void Controller::addCat(sf::Sprite sprite)
{
	sprite.move(16.f, 16.f);
	m_cats.emplace_back(90,sprite,m_level);
	m_cats[m_cats.size() - 1].setStartingPosition(sprite.getPosition());
}
//----------------------------------------------------------------------------
void Controller::initLevels() // read levels from the playlist
{
	std::ifstream input("Playlist.txt");
	if (!input) {
		std::cerr << "Couldnt open levels file!";
		exit(EXIT_FAILURE);
	}
	int size;
	input >> size;
	for (int i = 1; i <= size;i++) {
		std::string levelName = "Level" + std::to_string(i) + ".txt";
		m_levels.push_back(levelName);
	}

	input.close();
}
