#include <GameObjects/Key.h>
#include <iostream>



void Key::handleCollision(GameObject& object)
{
	object.handleCollision(*this);
}

void Key::handleCollision(Mouse& mouse)
{
	mouse.handleCollision(*this);
}