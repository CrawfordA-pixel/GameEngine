#pragma once
#include "Actor.h"

class Enemy : public Actor 
{
public:
	Enemy() = default;
	Enemy(const Transform& transform) : Actor{ transform } {}
	Enemy(const Transform& transform, Model* model) : Actor{ transform,model } {}
	Enemy(float speed, const Transform& transform, Model* model) : Actor{ transform,model }, m_sped{ speed } {}

	void Update(float dt);
	virtual void OnCollision(Actor* actor);

private:
	float m_sped = 10000;
	float m_fireTimer = 0;
};