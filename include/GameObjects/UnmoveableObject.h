#pragma once

#include "GameObject.h"

class UnmoveableObject : public GameObject {
public:
	using GameObject::GameObject;

	virtual void handleCollision(GameObject&) {};
	virtual void handleCollision(Wall&) {};
	virtual void handleCollision(Mouse&) {};
	virtual void handleCollision(Key&) {};
	virtual void handleCollision(Door&) {};
	virtual void handleCollision(Cheese&) {};
	virtual void handleCollision(KillCatPresent&) {};
	virtual void handleCollision(FreezeCatPresent&) {};
	virtual void handleCollision(AddLifePresent&) {};
	virtual void handleCollision(IncreaseTimePresent&) {};
	virtual void handleCollision(Cat&) {};
private:
};