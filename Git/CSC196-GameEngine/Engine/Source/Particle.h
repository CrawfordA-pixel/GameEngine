#pragma once
#include "Vector2.h"
#include "Renderer.h"
struct Particle
{
	struct Data
	{
		Vector2 position{ 0, 0 };
		Vector2 velocity{ 0, 0 };
		int r = 0;
		int g = 0;
		int b = 0;
		int a = 0;
		float lifespan = 0;
	};
	Vector2 position{ 0, 0 };
	Vector2 velocity{ 0, 0 };
	int r = 0;
	int g = 0;
	int b = 0;
	int a = 0;
	float lifespan = 0;
	bool isActive{ false };
	

	Particle() = default;
	Particle(Vector2 position, Vector2 velocity, float lifespan, int r, int g, int b, int a) : position{ position }, velocity{ velocity }, lifespan{ lifespan }, r { r }, g{ g }, b{ b }, a{ a } {}
	
	void Initialize(const Data& data);

	void Update(float dt);
	void Draw(Renderer& renderer);
};