#include "Player.h"
#include "Engine.h"
#include "Model.h"
#include "Bullet.h"
#include "Scene.h"
#include <iostream>


void Player::Update(float dt)
{
	//movement
	Vector2 direction{ 0,0 };
	m_transform.position.x = g_engine.GetInput().GetMousePosition().x;
	m_transform.position.y = g_engine.GetInput().GetMousePosition().y;
	SDL_HINT_WINDOW_FRAME_USABLE_WHILE_CURSOR_HIDDEN;
	SDL_ShowCursor(0);

	Vector2 acceleration = direction.Rotate(m_transform.rotation) * m_sped;

	m_velocity += acceleration * dt;

	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().GetWidth());
	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().GetHeight());

	//fire
	m_fireTimer -= dt;
	if (g_engine.GetInput().getMouseButtonDown(0) && m_fireTimer <= 0) {
		//if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && m_fireTimer <= 0) {// && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_SPACE)) {
		m_fireTimer = .2f * m_fireModifier;

		Vector2 direction = g_engine.GetInput().GetMousePosition() - m_transform.position;
		float angle = direction.Angle();
		std::vector<Vector2> points;
		points.push_back(Vector2{ 0.0f,2.0f });
		points.push_back(Vector2{ 1.0f,1.0f });
		points.push_back(Vector2{ 0.0f,2.0f });
		points.push_back(Vector2{ -1.0f,1.0f });
		points.push_back(Vector2{ 0.0f,-2.0f });
		points.push_back(Vector2{ 1.0f,-1.0f });
		points.push_back(Vector2{ 0.0f,-2.0f });
		points.push_back(Vector2{ -1.0f,-1.0f });
		points.push_back(Vector2{ 2.0f,0.0f });
		points.push_back(Vector2{ 1.0f,1.0f });
		points.push_back(Vector2{ -2.0f,0.0f });
		points.push_back(Vector2{ -1.0f,1.0f });
		points.push_back(Vector2{ 2.0f,0.0f });
		points.push_back(Vector2{ 1.0f,-1.0f });
		points.push_back(Vector2{ -2.0f,0.0f });
		points.push_back(Vector2{ -1.0f,-1.0f });

		Model* model = new Model{ points, Color(255.0f,0.0f,0.0f,255.0f) };
		Transform transform{ m_transform.position,angle,1.0f };



		auto bullet = std::make_unique<Bullet>(400, transform, model);
		bullet->SetLifespan(0.5f);
		bullet->SetTag("Player");
		m_scene->AddActor(std::move(bullet));

	}


	Actor::Update(dt);
}

void Player::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Enemy") {
		m_destroyed = true;
		//dynamic_cast<SpaceGame*>(m_scene->GetGame())->OnPlayerDeath();
	}

}