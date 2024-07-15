#define SDL_MAIN_HANDLED
#include "Engine.h"
#include <cstdlib>
#include <iostream>
#include <vector>

#define RENDERER = g_engine.GetRenderer()->
#define INPUT = g_engine.GetInput()

int main(int argc, char* argv[])
{

	g_engine.Initialize();
	bool end = false;
	
	Time time;

	g_engine.GetAudio()->AddSound("bass.wav");
	g_engine.GetAudio()->AddSound("snare.wav");
	g_engine.GetAudio()->AddSound("close-hat.wav");
	g_engine.GetAudio()->AddSound("open-hat.wav");
	g_engine.GetAudio()->AddSound("clap.wav");
	g_engine.GetAudio()->AddSound("cowbell.wav");


	std::vector<Particle> particles;
	float offset = 0;

	std::vector<Vector2> points;
	points.push_back(Vector2{ -5,5 });
	points.push_back(Vector2{ 0,-5 });
	points.push_back(Vector2{ 5,5 });
	points.push_back(Vector2{ -5,5 });
	Model model{ points, Color{1,1,1,0} };
	//Transform transform{ {g_engine.GetRenderer()->GetWidth() >> 1, g_engine.GetRenderer()->GetHeight() >> 1} 0,5};
	Vector2 position{ 400,300 };
	float rotation = 0;

	Vector2 v1{ 400, 300 };
	Vector2 v2{ 700, 500 };

	
	for (int i = 0; i < 10000; i++)
	{
		points.push_back(Vector2(rand() % 800, rand() % 600));
	}

	while (!end)
	{
		//Input
		time.Tick();
		std::cout << time.GetTime() << std::endl;
		g_engine.GetInput()->Update();
		if (g_engine.GetInput()->getKeyDown(SDL_SCANCODE_ESCAPE)) {
			end = true;
		}
		Vector2 velocity{ 0,0 };
		if (g_engine.GetInput()->getKeyDown(SDL_SCANCODE_UP)) velocity.y = -100;
		if (g_engine.GetInput()->getKeyDown(SDL_SCANCODE_DOWN)) velocity.y = 100;
		if (g_engine.GetInput()->getKeyDown(SDL_SCANCODE_LEFT)) velocity.x = -100;
		if (g_engine.GetInput()->getKeyDown(SDL_SCANCODE_RIGHT)) velocity.x = 100;

		if (g_engine.GetInput()->getKeyDown(SDL_SCANCODE_E))g_engine.GetAudio()->PlaySound("bass.wav");
		if (g_engine.GetInput()->getKeyDown(SDL_SCANCODE_R))g_engine.GetAudio()->PlaySound("snare.wav");
		if (g_engine.GetInput()->getKeyDown(SDL_SCANCODE_T))g_engine.GetAudio()->PlaySound("close-hat.wav");
		if (g_engine.GetInput()->getKeyDown(SDL_SCANCODE_Y))g_engine.GetAudio()->PlaySound("open-hat.wav");
		if (g_engine.GetInput()->getKeyDown(SDL_SCANCODE_Q))g_engine.GetAudio()->PlaySound("clap.wav");
		if (g_engine.GetInput()->getKeyDown(SDL_SCANCODE_W))g_engine.GetAudio()->PlaySound("cowbell.wav");



		position = position + velocity * time.GetDeltaTime();
		rotation = rotation + time.GetDeltaTime();

		Vector2 mousePosition = g_engine.GetInput()->GetMousePosition();
		if (g_engine.GetInput()->getMouseButtonDown(0) && !g_engine.GetInput()->getPrevMouseButtonDown(0))
		{
			for (int i = 0; i < 300; i++)
			{
				particles.push_back(Particle{ mousePosition, randomOnUnitCircle() * randomf(10, 200), 1.0f, random(255), random(255), random(255), 0 });
			}
		}
		
		for (Particle& particle : particles)
		{
			particle.Update(time.GetDeltaTime());
			if (particle.position.x > 800) particle.position.x = 0;
			if (particle.position.y > 600) particle.position.x = 0;
		}

		// clear screen
		g_engine.GetRenderer()->SetColor(0, 0, 0, 0);
		g_engine.GetRenderer()->BeginFrame();

		g_engine.GetRenderer()->SetColor(255, 255, 255, 0);
		float radius = 200;
		offset += (45 * time.GetDeltaTime());

		for (float angle = 0; angle < 360; angle += 360 / 30)
		{
			float x = Math::Cos(Math::DegToRad(angle + offset)) * Math::Sin(offset + angle) * 0.01f * radius;
			float y = Math::Sin(Math::DegToRad(angle + offset)) * Math::Sin(offset + angle) * 0.01f * radius;

			g_engine.GetRenderer()->SetColor(random(256), random(256), random(256), 0);
			g_engine.GetRenderer()->DrawRect(400 + x, 300 + y, 4.0f, 4.0f);
		}
		
		//draw particle
		g_engine.GetRenderer()->SetColor(255, 255, 255, 0);
		for (Particle particle : particles)
		{
			particle.Draw(*g_engine.GetRenderer());
		}
		model.Draw(*g_engine.GetRenderer(), position, rotation, 1);

		// show screen
		g_engine.GetRenderer()->endFrame();
		
	}

	return 0;
}