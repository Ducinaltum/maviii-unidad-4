#include "RagDoll.h"
#include <box2d/box2d.h>
#include "../Src/Box2DHelper.h"

RagDoll::RagDoll(b2World* world, b2Vec2 spawnPosition, float scale)
{
	m_force = 30;
	float density = 1.0f;
	float friction = 0.5f;
	float restitution = 0.5f;
	b2Vec2 torsoPosition(0, 0);
	b2Vec2 headPosition(0, -3.1f);
	b2Vec2 l_armPosition(-2, 0);
	b2Vec2 r_armPosition(2, 0);
	b2Vec2 l_legPosition(-1, 4.1f);
	b2Vec2 r_legPosition(1, 4.1f);

	torsoPosition *= scale;
	headPosition *= scale;
	l_armPosition *= scale;
	r_armPosition *= scale;
	l_legPosition *= scale;
	r_legPosition *= scale;

	torso = Box2DHelper::CreateRectangularDynamicBody(world, 2 * scale, 4 * scale, density, friction, restitution);
	torso->SetTransform(torsoPosition + spawnPosition, 0.0f);

	head = Box2DHelper::CreateCircularDynamicBody(world, 1 * scale, density, friction, restitution);
	head->SetTransform(headPosition + spawnPosition, 0.0f);
	b2Vec2 headAnchor(head->GetPosition());
	headAnchor.y += 1 * scale;

	l_arm = Box2DHelper::CreateRectangularDynamicBody(world, 1 * scale, 4 * scale, density, friction, restitution);
	l_arm->SetTransform(l_armPosition + spawnPosition, 0.0f);
	b2Vec2 l_armAnchor(l_arm->GetPosition());
	l_armAnchor.y -= 2 * scale;

	r_arm = Box2DHelper::CreateRectangularDynamicBody(world, 1 * scale, 4 * scale, density, friction, restitution);
	r_arm->SetTransform(r_armPosition + spawnPosition, 0.0f);
	b2Vec2 r_armAnchor(r_arm->GetPosition());
	r_armAnchor.y -= 2 * scale;

	l_Leg = Box2DHelper::CreateRectangularDynamicBody(world, 1 * scale, 4 * scale, density, friction, restitution);
	l_Leg->SetTransform(l_legPosition + spawnPosition, 0.0f);
	b2Vec2 l_LegAnchor(l_Leg->GetPosition());
	l_LegAnchor.y -= 2 * scale;

	r_Leg = Box2DHelper::CreateRectangularDynamicBody(world, 1 * scale, 4 * scale, density, friction, restitution);
	r_Leg->SetTransform(r_legPosition + spawnPosition, 0.0f);
	b2Vec2 r_LegAnchor(r_Leg->GetPosition());
	r_LegAnchor.y -= 2 * scale;

	b2Vec2 torsoHeadAnchor(torso->GetPosition());
	torsoHeadAnchor.y -= 2 * scale;
	b2Vec2 torsoLArmAnchor(torso->GetPosition());
	torsoLArmAnchor.x -= 1 * scale;
	torsoLArmAnchor.y -= 2 * scale;
	b2Vec2 torsoRArmAnchor(torso->GetPosition());
	torsoRArmAnchor.x += 1 * scale;
	torsoRArmAnchor.y -= 2 * scale;
	b2Vec2 torsoLLegAnchor(torso->GetPosition());
	torsoLLegAnchor.x -= 1 * scale;
	torsoLLegAnchor.y += 2 * scale;
	b2Vec2 torsoRLegAnchor(torso->GetPosition());
	torsoRLegAnchor.x += 1 * scale;
	torsoRLegAnchor.y += 2 * scale;

	b2DistanceJointDef headTorsoJointDef;
	headTorsoJointDef.Initialize(head, torso, headAnchor, torsoHeadAnchor);
	headTorsoJointDef.length = (headAnchor - torsoHeadAnchor).Length();
	headTorsoJointDef.collideConnected = true;
	world->CreateJoint(&headTorsoJointDef);


	b2DistanceJointDef l_armTorsoJointDef;
	l_armTorsoJointDef.Initialize(l_arm, torso, l_armAnchor, torsoLArmAnchor);
	l_armTorsoJointDef.length = (l_armAnchor - torsoLArmAnchor).Length();
	l_armTorsoJointDef.collideConnected = true;
	world->CreateJoint(&l_armTorsoJointDef);

	b2DistanceJointDef r_armTorsoJointDef;
	r_armTorsoJointDef.Initialize(r_arm, torso, r_armAnchor, torsoRArmAnchor);
	r_armTorsoJointDef.length = (r_armAnchor - torsoRArmAnchor).Length();
	r_armTorsoJointDef.collideConnected = true;
	world->CreateJoint(&r_armTorsoJointDef);

	b2DistanceJointDef l_LegTorsoJointDef;
	l_LegTorsoJointDef.Initialize(l_Leg, torso, l_LegAnchor, torsoLLegAnchor);
	l_LegTorsoJointDef.length = (l_LegAnchor - torsoLLegAnchor).Length();
	l_LegTorsoJointDef.collideConnected = true;
	world->CreateJoint(&l_LegTorsoJointDef);

	b2DistanceJointDef r_LegTorsoJointDef;
	r_LegTorsoJointDef.Initialize(r_Leg, torso, r_LegAnchor, torsoRLegAnchor);
	r_LegTorsoJointDef.length = (r_LegAnchor - torsoRLegAnchor).Length();
	r_LegTorsoJointDef.collideConnected = true;
	world->CreateJoint(&r_LegTorsoJointDef);
}

void RagDoll::ApplyForce(b2Vec2 force)
{
	torso->ApplyLinearImpulseToCenter(m_force * force, true);
}
