#include <iostream>
#include "GameObjects/IncreaseTimePresent.h"


void IncreaseTimePresent::handleCollision(GameObject& object)
{
	object.handleCollision(*this);
}

void IncreaseTimePresent::handleCollision(Mouse& mouse)
{
	mouse.handleCollision(*this);
}