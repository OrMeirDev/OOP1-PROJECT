#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameObjects/Wall.h"
#include "GameObjects/Cheese.h"
#include "GameObjects/UnmoveableObject.h"

class Controller;
class Mouse;


class Level {
public:
	Level(Controller& controller);
	void loadLevel(std::string levelName);
	void update(Mouse& mouse,sf::Time dt);
	void draw(sf::RenderWindow& window);
	void addTime(const int);
	void resetAllData();

	void clearObstacle(const int row, const int col);
	bool checkIfObstacle(const int row,const int col) const;
	//bool of can move 
	int getTime() const;

private:
	std::vector<std::vector<bool>> m_obstacles;
	std::vector <sf::Sprite> m_path;
	std::vector <UnmoveableObject*> m_objects;
	sf::Sprite createSprite(const std::string ,const int, const int,sf::Vector2f origin);
	void preventPass(sf::FloatRect, Mouse& mouse);
	Controller& m_controller;
	int m_cheeseCounter;
	int m_time;
	sf::Time m_timer;
};