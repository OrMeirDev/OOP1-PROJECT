#pragma once

#include "MovingObject.h"
class Key;
class Door;
class Cheese;
class KillCatPresent;
class FreezeCatPresent;
class AddLifePresent;
class IncreaseTimePresent;
class Controller;
class Level;

class Mouse : public MovingObject {
public:
	Mouse(Controller&,Level&);
	void setDirections();

	virtual void handleCollision(GameObject&);
	virtual void handleCollision(Wall&);
	virtual void handleCollision(Key&);
	virtual void handleCollision(Door&);
	virtual void handleCollision(Cheese&);
	virtual void handleCollision(KillCatPresent&);
	virtual void handleCollision(FreezeCatPresent&);
	virtual void handleCollision(AddLifePresent&); 
	virtual void handleCollision(IncreaseTimePresent&);
	virtual void handleCollision(Cat&);

	void resetAllData();
	void reduceLife();
	int getKeys() const;
	int getScore() const;
	int getLife() const;
private:
	int m_keys;
	int m_score;
	int m_life;
	Controller& m_controller;
	Level& m_level;
};