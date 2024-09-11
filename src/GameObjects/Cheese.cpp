#include <iostream>
#include "GameObjects/Cheese.h"

void Cheese::handleCollision(GameObject& object)
{
	object.handleCollision(*this);
}

void Cheese::handleCollision(Mouse& mouse)
{
	mouse.handleCollision(*this);
}