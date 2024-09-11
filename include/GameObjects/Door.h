#pragma once

#include "UnmoveableObject.h"
#include "GameObjects/Mouse.h"

class Door : public UnmoveableObject {
public:
	using UnmoveableObject::UnmoveableObject;
	virtual void handleCollision(GameObject&);
	virtual void handleCollision(Mouse&);
	sf::FloatRect isColidedWithDoor(Mouse& mouse);

private:

};