#include "ResourceManager.h"

ResourceManager ResourceManager::m_instance = ResourceManager();

ResourceManager::ResourceManager() {
	m_font.loadFromFile("font.ttf");
};

ResourceManager& ResourceManager::instance()
{
	return m_instance;
}
sf::SoundBuffer& ResourceManager::getSound(std::string soundName)
{
	if (m_sounds.find(soundName) != m_sounds.end()) { // if the texture exist return it 
		return m_sounds[soundName];
	}
	// else create and store in the hashing table 
	sf::SoundBuffer soundBuffer;
	soundBuffer.loadFromFile(soundName);
	m_sounds[soundName] = soundBuffer;
	return m_sounds[soundName];
}
const sf::Font& ResourceManager::getFont() const
{
	return m_font;
}
//texture name is the key to the hashing table and the texture is the value to store
sf::Texture& ResourceManager::getTexture(std::string textureName) // use hash table to store all the textures 
{
	if (m_textures.find(textureName) != m_textures.end()) { // if the texture exist return it 
		return m_textures[textureName];
	}
	// else create and store in the hashing table 
	sf::Texture texutre;
	texutre.loadFromFile(textureName);
	m_textures[textureName] = texutre;
	return m_textures[textureName];
}
