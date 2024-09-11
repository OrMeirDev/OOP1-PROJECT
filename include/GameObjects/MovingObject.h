#pragma once

#include "GameObject.h"
#include "consts.h"
#include <SFML/Graphics.hpp>

class MovingObject : public GameObject {
public:
	MovingObject() {
		m_movementSpeed = MOUSE_MOVEMENTSPEED;
		m_startingPos = getPosition();
	};
	MovingObject(float movementSpeed,sf::Sprite);
	void move(float deltaTime);
	void setDirection(Direction direction);
	Direction getDirection() const;
	void resetPosition();
	void setStartingPosition(sf::Vector2f pos);



	virtual void handleCollision(GameObject&) {};
	virtual void handleCollision(Wall&) {};
	virtual void handleCollision(Mouse&) {};
	virtual void handleCollision(Key&) {};
	virtual void handleCollision(Door&) {};
	virtual void handleCollision(Cheese&) {};
	virtual void handleCollision(KillCatPresent&) {};
	virtual void handleCollision(FreezeCatPresent&) {};
	virtual void handleCollision(AddLifePresent&) {};
	virtual void handleCollision(IncreaseTimePresent&) {};
	virtual void handleCollision(Cat&) {};
	
private:
	int m_movementSpeed;
	Direction m_dir;
	sf::Vector2f m_startingPos;
};