#include "GameObjects/MovingObject.h"
#include <iostream>

MovingObject::MovingObject(float movementSpeed, sf::Sprite sprite) :GameObject(sprite),m_movementSpeed(movementSpeed),m_dir(STANDING)
{}

void MovingObject::move(float deltaTime) // movment in real time 
{
	sf::Vector2f pos = getPosition();
	if(m_dir == LEFT){
		pos.x -= m_movementSpeed * deltaTime;
	}
	else if (m_dir == RIGHT) {
		pos.x += m_movementSpeed * deltaTime;
	}
	else if (m_dir == UP) {
		pos.y -= m_movementSpeed * deltaTime;
	}
	else if (m_dir == DOWN) {
		pos.y += m_movementSpeed * deltaTime;
	}
	setPosition(pos);
}

void MovingObject::setDirection(Direction direction) 
{
	m_dir = direction;
}

Direction MovingObject::getDirection() const
{
	return m_dir;
}

void MovingObject::resetPosition()
{
	setPosition(m_startingPos);
}

void MovingObject::setStartingPosition(sf::Vector2f pos)
{
	m_startingPos = pos;
}
