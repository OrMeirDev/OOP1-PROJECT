#pragma once

#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class ResourceManager {
public:
	ResourceManager();
	sf::Texture& getTexture(std::string filename);
	static ResourceManager& instance();
	sf::SoundBuffer& getSound(std::string filename);
	const sf::Font& getFont() const;
	
private:
	ResourceManager(const ResourceManager& other) = default;
	ResourceManager& operator=(const ResourceManager& other) = default;
	static ResourceManager m_instance;

	std::unordered_map<std::string, sf::Texture> m_textures;
	std::unordered_map<std::string, sf::SoundBuffer> m_sounds;
	sf::Font m_font;
};