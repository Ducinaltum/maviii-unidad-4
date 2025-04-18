#include "Cannon.h"
#include <iostream>
#include <algorithm>

Cannon::Cannon(sf::Vector2f position)
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

	m_base->setScale(0.1f, 0.1f);
	m_cannon->setScale(0.1f, 0.1f);

	m_base->setOrigin(m_base->getLocalBounds().width / 2, m_cannon->getLocalBounds().height / 2);
	m_cannon->setOrigin(m_cannon->getLocalBounds().height / 2, m_cannon->getLocalBounds().height / 2);

	m_base->setPosition(position);
	m_cannon->setPosition(position);
}

void Cannon::Update(b2Vec2 mousePos)
{
	b2Vec2 cannonPos(m_cannon->getPosition().x, m_cannon->getPosition().y);
	b2Vec2 direction = mousePos - cannonPos; 
	float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159265f;
	if (angle > 0) angle = 0;
	else if (angle < -90 ) angle = -90;
	m_cannon->setRotation(angle);
	if (m_isShooting)
	{
		m_isShooting = false;
		float strength = direction.Length();
	}
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
