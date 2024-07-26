#define SDL_MAIN_HANDLED
#include "Engine.h"
#include <iostream>
#include <SDL.h>
#include <vector>
#include <cstdlib>

int main(int argc, char* argv[]) 
{
	//initialize engine
	g_engine.Initialize();

	bool end = false;
	while (!end) {
		g_engine.GetInput().Update();
		if (g_engine.GetInput().getKeyDown(SDL_SCANCODE_ESCAPE)) {
			end = true;
		}
		if (g_engine.GetInput().getKeyDown(SDL_SCANCODE_Q) && !g_engine.GetInput().getPrevKeyDown(SDL_SCANCODE_Q))g_engine.GetAudio().PlaySound("bass.wav");
		if (g_engine.GetInput().getKeyDown(SDL_SCANCODE_A) && !g_engine.GetInput().getPrevKeyDown(SDL_SCANCODE_A))g_engine.GetAudio().PlaySound("snare.wav");
		if (g_engine.GetInput().getKeyDown(SDL_SCANCODE_Z) && !g_engine.GetInput().getPrevKeyDown(SDL_SCANCODE_Z))g_engine.GetAudio().AddSound("open-hat.wav");
		if (g_engine.GetInput().getKeyDown(SDL_SCANCODE_X) && !g_engine.GetInput().getPrevKeyDown(SDL_SCANCODE_X))g_engine.GetAudio().AddSound("close-hat.wav");
		if (g_engine.GetInput().getKeyDown(SDL_SCANCODE_S) && !g_engine.GetInput().getPrevKeyDown(SDL_SCANCODE_S))g_engine.GetAudio().AddSound("clap.wav");
		if (g_engine.GetInput().getKeyDown(SDL_SCANCODE_W) && !g_engine.GetInput().getPrevKeyDown(SDL_SCANCODE_W))g_engine.GetAudio().AddSound("cowbell.wav");

		g_engine.GetAudio().Update();
	}
	return 0;
}