#include <iostream>
#include "GameObjects/FreezeCatPresent.h"


void FreezeCatPresent::handleCollision(GameObject& object)
{
	object.handleCollision(*this);
}

void FreezeCatPresent::handleCollision(Mouse& mouse)
{
	mouse.handleCollision(*this);
}