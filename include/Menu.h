#pragma once
#include "Controller.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class Menu {
public:
	Menu();
	void launch();
	void setGameOver(bool b);
	void setEndGameOpen(bool b);
	void drawGameOver(sf::RenderWindow& window);
	void drawEndScreen(sf::RenderWindow& window);

private:
	Controller m_controller;
	
	sf::Sprite m_newGameButton;
	sf::Sprite m_helpButton;
	sf::Sprite m_exitButton;
	sf::Sprite m_backGround;
	sf::Sprite m_backToMenu;

	void drawMenu(sf::RenderWindow& window);
	void handleClick(sf::Event event,sf::RenderWindow& window);


	bool m_isGameOpen;
	bool m_isGameOverOpen;
	bool m_isEndGameOpen;

	sf::Music m_music;
};