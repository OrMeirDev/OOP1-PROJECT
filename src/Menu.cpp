#include "consts.h"
#include <SFML/Graphics.hpp>
#include "Controller.h"
#include "Menu.h"
#include <iostream>
#include "ResourceManager.h"

Menu::Menu():m_isGameOpen(false),m_isGameOverOpen(false),m_controller(*this),m_isEndGameOpen(false)
{
	m_newGameButton.setTexture(ResourceManager::instance().getTexture(NEWGAME_TEXTURE));
	m_helpButton.setTexture(ResourceManager::instance().getTexture(HELP_TEXTURE));
	m_exitButton.setTexture(ResourceManager::instance().getTexture(EXIT_TEXTURE));
	m_backGround.setTexture(ResourceManager::instance().getTexture(BACKGROUND_TEXTURE));
	m_backToMenu.setTexture(ResourceManager::instance().getTexture(BACKTOMENU_TEXTURE));
}

void Menu::launch()
{
	
		sf::Clock clock;
		sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Good Game", sf::Style::Close | sf::Style::Titlebar);
		window.setFramerateLimit(240);

		while (window.isOpen()) {
			sf::Event event;
			window.clear();

			// Input
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}
				if (!m_isGameOpen) {
					handleClick(event, window);
				}
				else {
					m_controller.handleInput(event);
				}
			}
			sf::Time dt = clock.restart();
			if (m_isEndGameOpen) {
				drawEndScreen(window);
				window.display();
				continue;
			}
			if (!m_isGameOverOpen) {
				// Update
				if (m_isGameOpen) {
					m_controller.update(dt);
				}

				// Draw
				if (!m_isGameOpen) {
					drawMenu(window);
				}
				else {
					window.clear();
					m_controller.draw(window);


				}
			}
			else {
				window.clear();
				drawGameOver(window);
			}

			window.display();
		}
}

void Menu::setGameOver(bool b)
{
	m_isGameOverOpen = b;
	m_isGameOpen = false;
}

void Menu::setEndGameOpen(bool b)
{
	m_isEndGameOpen = b;
	m_isGameOpen = false;
}

void Menu::drawGameOver(sf::RenderWindow& window)
{
	sf::Sprite sprite;
	sprite.setTexture(ResourceManager::instance().getTexture(GAMEOVER_TEXTURE));
	window.draw(sprite);
	m_backToMenu.setPosition(sf::Vector2f(20, 390));
	window.draw(m_backToMenu);
	m_exitButton.setPosition(sf::Vector2f(20, 530));
	window.draw(m_exitButton);
	sf::Event event;
	
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::MouseButtonPressed) {
			sf::Vector2i mousePress = sf::Mouse::getPosition(window);
			sf::Vector2f mousePosFloat(static_cast<float>(mousePress.x), static_cast<float>(mousePress.y));


			if (m_exitButton.getGlobalBounds().contains(mousePosFloat)) { // Exit
				window.close();
			}
			else if (m_backToMenu.getGlobalBounds().contains(mousePosFloat))
			{
				this->launch();
			}
		}
	}

}

void Menu::drawEndScreen(sf::RenderWindow& window)
{
	sf::Sprite sprite;
	sprite.setTexture(ResourceManager::instance().getTexture(ENDGAME_TEXTURE));
	window.draw(sprite);
	m_backToMenu.setPosition(sf::Vector2f(20, 390));
	window.draw(m_backToMenu);
	m_exitButton.setPosition(sf::Vector2f(20, 530));
	window.draw(m_exitButton);
	
}

void Menu::drawMenu(sf::RenderWindow& window)
{
	sf::Sprite cartoon;
	cartoon.setTexture(ResourceManager::instance().getTexture(CAT_CARTOON));
	cartoon.setPosition(sf::Vector2f(600,250));
	m_newGameButton.setPosition(sf::Vector2f(30,50));
	m_helpButton.setPosition(sf::Vector2f(20, 390));
	m_exitButton.setPosition(sf::Vector2f(20,530));
	m_backGround.setPosition(sf::Vector2f(0,0));

	window.draw(m_backGround);
	window.draw(m_helpButton);
	window.draw(m_newGameButton);
	window.draw(m_exitButton);
	window.draw(cartoon);
}

void Menu::handleClick(sf::Event event, sf::RenderWindow& window)
{
	// All Events
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.key.code == sf::Mouse::Left) {
			sf::Vector2f pos = window.mapPixelToCoords({ event.mouseButton.x,event.mouseButton.y });
			
			if (!m_isEndGameOpen) {
				if (m_newGameButton.getGlobalBounds().contains(pos)) { // New Game Clicked
					m_isGameOpen = true;
					m_controller.resetAllData();
					m_controller.run();
					m_music.openFromFile("music.ogg");
					m_music.setLoop(true);
					m_music.setVolume(50);
					m_music.play();
				}

				if (m_helpButton.getGlobalBounds().contains(pos)) { // Help Clicked

					sf::Sprite help;
					sf::RenderWindow helpwindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "help", sf::Style::Close | sf::Style::Titlebar);
					helpwindow.setFramerateLimit(60);
					help.setTexture(ResourceManager::instance().getTexture(HELPSCREEN_TEXTURE));
					help.setPosition(0, 0);

					while (helpwindow.isOpen())
					{
						sf::Event event;
						helpwindow.clear();
						helpwindow.draw(help);
						// Input
						while (helpwindow.pollEvent(event)) {
							if (event.type == sf::Event::Closed) {
								helpwindow.close();
							}
						}
						helpwindow.display();
					}
				}
			}
			else {
				if (m_backToMenu.getGlobalBounds().contains(pos)) {
					m_isEndGameOpen = false;
					m_isGameOpen = false;
				}
			}

			if (m_exitButton.getGlobalBounds().contains(pos)) { // Exit clicked
				window.close();
			}
		}
	}

}
