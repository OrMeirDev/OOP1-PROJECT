#include "GameObjects/Mouse.h"

#include <SFML/Graphics.hpp>
#include "consts.h"
#include <iostream>
#include "Controller.h"

Mouse::Mouse(Controller& controller,Level& level) : m_keys(0), m_life(3), m_score(0),m_controller(controller),
m_level(level)
{
	
}

void Mouse::setDirections() // movment 
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		setDirection(LEFT);
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		setDirection(RIGHT);
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		setDirection(DOWN);
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		setDirection(UP);
		return;
	}
	setDirection(STANDING);
}

void Mouse::handleCollision(GameObject& object)
{
	object.handleCollision(*this);
}

void Mouse::handleCollision(Wall& wall)
{

}

void Mouse::handleCollision(Key& key)
{
	m_keys++;
	m_controller.playSound(KEY_SOUND);
}

void Mouse::handleCollision(Door& door)
{

	if (m_keys > 0) {
		m_keys--;
	}
	sf::Vector2f pos = getPosition();
	m_level.clearObstacle((int)pos.y / 32, (int)pos.x / 32);
	m_controller.playSound(DOOR_SOUND);
}

void Mouse::handleCollision(Cheese& cheese)
{
	m_score += 10;
	m_controller.playSound(EAT_SOUND);
}

void Mouse::handleCollision(KillCatPresent&)
{
	m_score += 5;
	m_controller.killCat();
	m_controller.playSound(KILL_SOUND);
}
void Mouse::handleCollision(FreezeCatPresent&)
{
	//freeze cat
	m_score += 5;
	m_controller.freezeCats();
	m_controller.playSound(FREEZE_SOUND);
}

void Mouse::handleCollision(AddLifePresent&)
{
	m_score += 5;
	m_life++;
	m_controller.playSound(LIFE_SOUND);
}

void Mouse::handleCollision(IncreaseTimePresent&)
{
	m_score += 5;
	m_controller.addTime();
	m_controller.playSound(TIME_SOUND);
}

void Mouse::handleCollision(Cat&)
{
	m_life--;
	resetPosition();
	m_controller.resetAllCats();
	if (m_life == 0) {
		m_controller.gameOver();
	}
	m_controller.playSound(DEAD_SOUND);
}

void Mouse::resetAllData()
{
	m_score = 0;
	m_life = 3;
	m_keys = 0;
}

void Mouse::reduceLife()
{
	m_life--;
}

int Mouse::getKeys() const{
	return m_keys;
}

int Mouse::getScore() const{
	return m_score;
}

int Mouse::getLife() const{
	return m_life;
}
