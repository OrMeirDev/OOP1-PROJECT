#include <iostream>
#include "GameObjects/AddLifePresent.h"

void AddLifePresent::handleCollision(GameObject& object)
{
	object.handleCollision(*this);
}

void AddLifePresent::handleCollision(Mouse& mouse)
{
	mouse.handleCollision(*this);
}