#include "Level.h"
#include <fstream>
#include <iostream>
#include "GameObject.h"
#include "consts.h"
#include "Controller.h"
#include "ResourceManager.h"
#include "GameObjects/Mouse.h"
#include "GameObjects/Cheese.h"
#include "GameObjects/Door.h"
#include "GameObjects/Key.h"
#include "GameObjects/AddLifePresent.h"
#include "GameObjects/FreezeCatPresent.h"
#include "GameObjects/IncreaseTimePresent.h"
#include "GameObjects/KillCatPresent.h"
#include<typeinfo>



Level::Level(Controller& controller):m_controller(controller),m_cheeseCounter(0),m_time(0)
{
	m_timer = sf::Time::Zero;
}

void Level::loadLevel(std::string levelName)
{
	std::ifstream levelFile(levelName);
	if (!levelFile) {
		std::cerr << "Couldnt open level.";
		exit(EXIT_FAILURE);
	}
	levelFile >> m_time;
	levelFile.get();
	int row = 0;
	std::string currentLine;
	m_objects.clear();
	m_obstacles.clear();
	m_path.clear();
	m_cheeseCounter = 0;
	
	while (std::getline(levelFile, currentLine)) {
		std::vector<bool> obstacels_row(COLS, false);
		m_obstacles.push_back(obstacels_row);
		for (int col = 0;currentLine[col] != '\0';col++) {
			if (currentLine[col] == '#') { // Wall
				m_objects.emplace_back(new Wall(createSprite(WALL_TEXTURE, row, col, sf::Vector2f(0, 0))));
				m_obstacles[row][col] = true;
			}
			if (currentLine[col] != '#') { // Path
				m_path.push_back(createSprite(PATH_TEXTURE, row, col, sf::Vector2f(0, 0)));
			}
			if (currentLine[col] == '%') { // Mouse
				m_controller.setMouse(createSprite(MOUSE_TEXTURE, row, col, sf::Vector2f(0, 0)));
			}
			if (currentLine[col] == '*') { //cheese
				m_objects.push_back(new Cheese(createSprite(CHEESE_TEXTURE, row, col, sf::Vector2f(0, 0))));
				m_cheeseCounter++;
			}
			if (currentLine[col] == 'F') { // Key
				m_objects.push_back(new Key(createSprite(KEY_TEXTURE, row, col, sf::Vector2f(0, 0))));
			}
			if (currentLine[col] == 'D') { //Door
				m_objects.emplace_back(new Door(createSprite(DOOR_TEXTURE, row, col, sf::Vector2f(0, 0))));
				m_obstacles[row][col] = true;
			}
			if (currentLine[col] == '!') { // Freeze
				m_objects.push_back(new FreezeCatPresent(createSprite(FREEZE_TEXTURE, row, col, sf::Vector2f(0, 0))));
			}
			if (currentLine[col] == '.') { // Time Present
				m_objects.push_back(new IncreaseTimePresent(createSprite(TIME_TEXTURE,row,col, sf::Vector2f(0, 0))));
			}
			if (currentLine[col] == '@') { // Life
				m_objects.push_back(new AddLifePresent(createSprite(LIFE_TEXTURE, row, col, sf::Vector2f(0, 0))));
			}
			if (currentLine[col] == '$') { // Kill cat
				m_objects.push_back(new KillCatPresent(createSprite(KILLCAT_TEXTURE, row, col, sf::Vector2f(0, 0))));
			}
			if (currentLine[col] == '^') { // cat
				m_controller.addCat(createSprite(CAT_TEXTURE, row, col, sf::Vector2f(16, 16)));
			}
		}
		row++;
	}
	levelFile.close();
}

void Level::update(Mouse& mouse, sf::Time dt)
{
	if (m_timer >= sf::seconds(1.f)) {
		m_time--;
		m_timer = sf::Time::Zero;
	}
	else {
		m_timer += dt;
	}

	for (int i = 0; i < m_objects.size(); i++) {
		
		if (m_objects[i]->isColided(mouse))
		{
			if (typeid(*m_objects[i]) == typeid(Door)) {
				bool canopendoor = mouse.getKeys() > 0 ? true : false;
				Door* door = dynamic_cast<Door*>(m_objects[i]);
				sf::FloatRect result = door->isColidedWithDoor(mouse);

				if (!canopendoor) {
					preventPass(result, mouse);
					continue;
				}
			}
			mouse.handleCollision(*m_objects[i]);
			if (typeid(*m_objects[i]) == typeid(Wall)) {
				Wall* wall = dynamic_cast<Wall*>(m_objects[i]);
				sf::FloatRect result = wall->isColidedWithWall(mouse);
				sf::Vector2f pos = mouse.getPosition();
				preventPass(result, mouse);
				continue;
			}
			if (typeid(*m_objects[i]) == typeid(Cheese)){
				m_cheeseCounter--;
				if (m_cheeseCounter == 0){
					m_controller.updateLevel();
					m_controller.run();
				}
			}
			
			m_objects.erase(m_objects.begin() + i);
		}
	}
}
//----------------------------------------------------------------------------
void Level::draw(sf::RenderWindow& window)
{
	for (sf::Sprite& sprite : m_path) {
		window.draw(sprite);
	}
	for (UnmoveableObject* object  : m_objects)
	{
		object->draw(window);
	}

}
void Level::addTime(const int time)
{
	m_time += time;
}

void Level::resetAllData()
{
	m_path.clear();
	m_obstacles.clear();
	m_objects.clear();
	m_cheeseCounter = 0;
}

void Level::clearObstacle(const int row, const int col)
{
	m_obstacles[row][col] = false;
}

bool Level::checkIfObstacle(const int row,const int col) const
{
	return m_obstacles[row][col];
}

int Level::getTime() const
{
	return m_time;
}
//----------------------------------------------------------------------------
sf::Sprite Level::createSprite(const std::string texture , const int row , const int col
	, sf::Vector2f origin)
{
	sf::Sprite sprite;
	sprite.setPosition(sf::Vector2f(col * TEXTURESIZE, row * TEXTURESIZE));
	sprite.setTexture(ResourceManager::instance().getTexture(texture));
	sprite.setOrigin(origin);
	return sprite;
}
//----------------------------------------------------------------------------
void Level::preventPass(sf::FloatRect result, Mouse& mouse)
{
	sf::Vector2f pos = mouse.getPosition();
	if (result.height < 9) {
		pos.y = pos.y < result.top ? pos.y - result.height : pos.y + result.height;
	}
	if (result.width < 9) {
		pos.x = pos.x < result.left ? pos.x - result.width : pos.x + result.width;
	}
	mouse.setPosition(pos);
}


// Cat
