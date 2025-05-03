#include "Cannon.h"
#include <iostream>
#include <algorithm>

Cannon::Cannon(sf::Vector2f position) :
	m_barrelSpawnPosition(0,0)
{
	m_position = position;
	m_angle = 0;

	m_baseTex = new sf::Texture();
	m_cannonTex = new sf::Texture();
	m_baseTex->loadFromFile("../Src/Assets/CannonBase.png");
	m_cannonTex->loadFromFile("../Src/Assets/Cannon.png");

	m_base = new sf::Sprite();
	m_base->setTexture(*m_baseTex);
	m_cannon = new sf::Sprite();
	m_cannon->setTexture(*m_cannonTex);
	m_barrelSpawnPosition.x = m_cannon->getLocalBounds().width;
	m_barrelSpawnPosition.y = m_cannon->getLocalBounds().height / 2;

	m_base->setScale(0.1f, 0.1f);
	m_cannon->setScale(0.1f, 0.1f);

	m_base->setOrigin(m_base->getLocalBounds().width / 2, m_cannon->getLocalBounds().height / 2);
	m_cannon->setOrigin(m_cannon->getLocalBounds().height / 2, m_cannon->getLocalBounds().height / 2);

	m_base->setPosition(position);
	m_cannon->setPosition(position);
}

b2Vec2 Cannon::GetPosition()
{
	b2Vec2 cannonPos(m_cannon->getPosition().x, m_cannon->getPosition().y);
	return cannonPos;
}

b2Vec2 Cannon::GetProjectileExitPosition()
{
	sf::Vector2f pos = m_cannon->getTransform().transformPoint(m_barrelSpawnPosition);
	b2Vec2 spawnPos(pos.x, pos.y);
	return spawnPos;

}

void Cannon::Update(b2Vec2 mousePos)
{
	b2Vec2 cannonPos(m_cannon->getPosition().x, m_cannon->getPosition().y);
	b2Vec2 direction = mousePos - cannonPos; 
	if (direction.x < 0) direction.x = 0;
	if (direction.y > 0) direction.y = 0;
	float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159265f;
	m_cannon->setRotation(angle);
}

void Cannon::Draw(sf::RenderWindow* wnd)
{
	wnd->draw(*m_cannon);
	wnd->draw(*m_base);
}

void Cannon::Shoot()
{
	m_isShooting = true;
}
