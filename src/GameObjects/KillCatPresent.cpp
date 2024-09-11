#include <GameObjects/KillCatPresent.h>
#include <iostream>

void KillCatPresent::handleCollision(GameObject& object)
{
	object.handleCollision(*this);
}
void KillCatPresent::handleCollision(Mouse& mouse)
{
	mouse.handleCollision(*this);
}
