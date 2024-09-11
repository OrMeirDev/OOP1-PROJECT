#pragma once
#include <SFML/Graphics.hpp>



class Wall;
class Mouse;
class Key;
class Door;
class Cheese;
class KillCatPresent;
class FreezeCatPresent;
class AddLifePresent;
class IncreaseTimePresent;
class Cat;

class GameObject {
public:
	GameObject() {};
	GameObject(sf::Sprite);
	virtual void draw(sf::RenderWindow& window);

	sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f pos);
	void setSprite(sf::Sprite sprite);
	bool isColided(GameObject& other);
	sf::FloatRect getGlobalBounds() const;

	// Double Dispatch
	virtual void handleCollision(GameObject&) = 0;
	virtual void handleCollision(Wall&) = 0;
	virtual void handleCollision(Mouse&) = 0;
	virtual void handleCollision(Key& ) = 0;
	virtual void handleCollision(Door&) = 0;
	virtual void handleCollision(Cheese&) = 0;
	virtual void handleCollision(KillCatPresent&) = 0;
	virtual void handleCollision(FreezeCatPresent&) = 0;
	virtual void handleCollision(AddLifePresent&) = 0;
	virtual void handleCollision(IncreaseTimePresent&) = 0;
	virtual void handleCollision(Cat&) = 0;
private:
	sf::Sprite m_sprite;
};

