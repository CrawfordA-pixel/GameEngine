#define SDL_MAIN_HANDLED
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Scene.h"
#include "Font.h"
#include "Text.h"
#include <iostream>
#include <SDL.h>
#include <vector>
#include <cstdlib>

int main(int argc, char* argv[]) 
{
	//initialize engine
	g_engine.Initialize();
	
	//timing
	Time time;

	//particle system
	std::vector<Particle> particles;
	float offset = 0;

	//font
	Font* font = new Font;
	font->Load("Anomaly Nexus Demo.otf", 40);

	Text* greeting = new Text(font);
	greeting->Create(g_engine.GetRenderer(), "Hello Aimer!", Color{ 1,0,0,1 });

	//model
	std::vector<Vector2> points;
	points.push_back(Vector2{ 0,3 });
	points.push_back(Vector2{ 0,-3 });
	points.push_back(Vector2{ -3,0 });
	points.push_back(Vector2{ 3,0 });
	
	//actor
	Model* model = new Model{ points, Color(1,1,1,0) };
	Scene* scene = new Scene();

	Transform transform{ Vector2{400,300},0,1};
	auto player = std::make_unique<Player>(randomf(300, 500), transform, model);
	player->SetDamping(2.0f);
	player->SetTag("Player");
	scene->AddActor(std::move(player));


	bool end = false;
	while (!end) {
		//Input
		time.Tick();
		g_engine.GetInput().Update();

		if (g_engine.GetInput().getKeyDown(SDL_SCANCODE_ESCAPE)) {
			end = true;
		}

		//mouse input
		Vector2 mousePosition = g_engine.GetInput().GetMousePosition();

		//Update
		scene->Update(time.GetDeltaTime());

		//screen wrap
		for (Particle& particle : particles) {
			g_engine.GetRenderer().SetColor(255, 255, 255, 0);
			particle.Update(time.GetDeltaTime());
			if (particle.position.x > 800) particle.position.x = 0;
			if (particle.position.x < 0) particle.position.x = 800;
		}

		//clear screen
		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();
		//change screen
		g_engine.GetRenderer().SetColor(255, 255, 255, 0);
		greeting->Draw(g_engine.GetRenderer(), 40, 40);
		scene->Draw(g_engine.GetRenderer());
		//show screen
		g_engine.GetRenderer().EndFrame();
	}
	return 0;
}