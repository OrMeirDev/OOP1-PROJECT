#pragma once

#include "UnmoveableObject.h"
#include <SFML/Graphics.hpp>

class Wall : public UnmoveableObject {
public:
	using UnmoveableObject::UnmoveableObject;
	virtual void handleCollision(GameObject&);
	virtual void handleCollision(Mouse& mouse);
	sf::FloatRect isColidedWithWall(Mouse& mouse);
private:

};