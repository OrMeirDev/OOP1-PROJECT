#include "GameObjects/Wall.h"
#include <iostream>
#include "GameObjects/Mouse.h"


void Wall::handleCollision(GameObject& object)
{
	object.handleCollision(*this);
}


void Wall::handleCollision(Mouse& mouse)
{
}

sf::FloatRect Wall::isColidedWithWall(Mouse& mouse)
{
	sf::FloatRect result;
	mouse.getGlobalBounds().intersects(getGlobalBounds(), result);
	return result;
}
