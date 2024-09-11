#pragma once
#include "GameObjects/MovingObject.h"
#include "GameObjects/Wall.h"
#include "GameObjects/Door.h"
#include <vector>

class Level;

class Cat :public MovingObject { 
public:
	Cat(int movementSpeed,sf::Sprite sprite,Level&);
	void setDirections(sf::Vector2f mousePos);
	virtual void handleCollision(GameObject&);
private:
	Level& m_level;
};