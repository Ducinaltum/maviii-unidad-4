#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
class Cannon
{
private:
	sf::Vector2f m_position;
	sf::Vector2f m_barrelSpawnPosition;
	float m_angle;
	bool m_isShooting;

	sf::Texture * m_baseTex;
	sf::Texture * m_cannonTex;
	sf::Sprite * m_base;
	sf::Sprite * m_cannon;
public:
	Cannon(sf::Vector2f position);
	b2Vec2 GetPosition();
	b2Vec2 GetProjectileExitPosition();
	void Update(b2Vec2 mousePos);
	void Draw(sf::RenderWindow* wnd);
	void Shoot();
};

