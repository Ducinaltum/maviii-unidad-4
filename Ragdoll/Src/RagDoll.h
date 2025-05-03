#pragma once
#include <box2d/box2d.h>

class RagDoll
{
private:
	// Cuerpo de box2d
	b2Body* head;
	b2Body* torso;
	b2Body* l_Leg;
	b2Body* r_Leg;
	b2Body* l_arm;
	b2Body* r_arm;
	float m_force;
public:
	RagDoll(b2World* world, b2Vec2 spawnPosition, float scale = 1);
	void ApplyForce(b2Vec2 force);
};

