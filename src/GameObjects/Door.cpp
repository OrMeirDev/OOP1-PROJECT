#include <iostream>
#include "GameObjects/Door.h"


void Door::handleCollision(GameObject& object)
{
	object.handleCollision(*this);
}

void Door::handleCollision(Mouse& mouse)
{
	mouse.handleCollision(*this);
}

sf::FloatRect Door::isColidedWithDoor(Mouse& mouse)
{
	sf::FloatRect result;
	mouse.getGlobalBounds().intersects(getGlobalBounds(), result);
	return result;
}
