#include <Windows.h>
#include <SDL.h>
#include <iostream>
#include "Game.h"
#include "GameSettings.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		SDL_Log("Error : %s\n", SDL_GetError());
		return 1;
	}

	SDL_Window* win = SDL_CreateWindow(
		"Space Invaders",
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_UTILITY
	);

	SDL_Renderer* renderer = SDL_CreateRenderer(win, 0, SDL_RENDERER_PRESENTVSYNC);

	if (renderer == nullptr)
	{
		SDL_Log("Error : %s\n", SDL_GetError());
		return 1;
	}

	bool running = true;
	SDL_Event e;

	Game* game = new Game(renderer);

	while (running)
	{
		while (SDL_PollEvent(&e))
		{
			//If mouse event happened
			if (e.type == SDL_MOUSEMOTION )
			{
				//Get mouse position
				int x, y;
				SDL_GetMouseState(&x, &y);
				game->MouseMotion(x, y);
				
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				game->MouseButtonDown(x, y);
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		game->Update();
		game->Draw();

		// Push back buffer to the front buffer
		SDL_RenderPresent(renderer);
	}

	if (game != nullptr)
	{
		delete game;
		game = nullptr;
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();

	SDL_Log("PROGRAM END\n");
	return 0;
}
