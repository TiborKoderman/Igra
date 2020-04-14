#include "SDL.h"
#include "Game.h"

Game* game = nullptr;




int main(int argc, char* argv[])
{
	game = new Game();

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	double frameTime;

	game->init("Igra", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowWidth, WindowHeight, 0);

	while (game->running())
	{

		frameStart = SDL_GetTicks();

		game->handleEvents();
 		game->update();
		game->render();
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	
	game->clean();
	delete game;
	return 0;
}