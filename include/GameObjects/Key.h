#pragma once

#include "UnmoveableObject.h"
#include <GameObjects/Mouse.h>
class Mouse;

class Key : public UnmoveableObject {
public:
	using UnmoveableObject::UnmoveableObject;

	virtual void handleCollision(GameObject&);
	virtual void handleCollision(Mouse&);

private:

};