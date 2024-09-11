#include "GameObject.h"

GameObject::GameObject(sf::Sprite sprite):m_sprite(sprite)
{

}

void GameObject::draw(sf::RenderWindow& window) 
{
	window.draw(m_sprite);
}

sf::Vector2f GameObject::getPosition() const
{
	return m_sprite.getPosition();
}

void GameObject::setPosition(sf::Vector2f pos)
{
	m_sprite.setPosition(pos);
}

void GameObject::setSprite(sf::Sprite sprite)
{
	m_sprite = sprite;
}

bool GameObject::isColided(GameObject& other)
{
	return m_sprite.getGlobalBounds().intersects(other.getGlobalBounds());
}

sf::FloatRect GameObject::getGlobalBounds() const // bounding rectangle of the object 
{
	return m_sprite.getGlobalBounds();
}
