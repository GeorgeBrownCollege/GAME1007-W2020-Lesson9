#include "Game.h"
#include <iostream>
#include <SDL_image.h>

Game::Game()
{
}

Game::Game(const char* windowName, int windowSizeX, int windowSizeY)
{
	int flags = SDL_INIT_EVERYTHING;

	if (SDL_Init(flags) == 0) // if initialized SDL correctly...
	{
		// Create the window
		pWindow = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowSizeX, windowSizeY, SDL_WINDOW_SHOWN);

		if (pWindow != nullptr)
		{
			// Create the renderer
			pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_PRESENTVSYNC);

			if (pRenderer != nullptr)
			{
				IMG_Init(IMG_INIT_PNG);
			}
		}
	}
}

Game::~Game()
{
}

void Game::run()
{
	ship = Sprite(pRenderer, "ship.png", 140, 140);
	background = Sprite(pRenderer, "ship.png", 800, 600);
	background.setPosition(0,0);
	ship.setPosition(0, 0);



	isRunning = true;
	
	// set initial delta time
	deltaTime = 1.0f / targetFramerate;
	lastFrameStartTimeMs = SDL_GetTicks();

	while (isRunning)
	{
		input();
		update();
		draw();
		waitForNextFrame();
	}

	cleanup();
}

void Game::input()
{
}

void Game::update()
{
	// transforming ship based on sinosoidal function of time
	// for fun!
	ship.velX = sin(gameTime) * 100;
	ship.velY = sin(gameTime) * 100;

	ship.dst.x = ship.dst.x + ship.velX * deltaTime;
	ship.dst.y = ship.dst.y + ship.velY * deltaTime;

	//ship.setPosition(400, sin((float)SDL_GetTicks() / 1000.f) * 200 + 200);
	ship.setSize(sin(gameTime * 100) + 100, sin(gameTime) * 100 + 100);

	// automatically quit after 30 seconds just as an example to show Qame.quit()
	if (gameTime > 30)
	{
		std::cout << "automatically quitting -- 30 seconds have passed" << std::endl;
		quit();
	}
}

void Game::draw()
{
	SDL_SetRenderDrawColor(pRenderer, 255, 205, 90, 255);
	SDL_RenderClear(pRenderer);
	
	background.draw(pRenderer);
	ship.draw(pRenderer);
	
	SDL_RenderPresent(pRenderer);
}

void Game::waitForNextFrame()
{
	Uint32 gameTimeMs = SDL_GetTicks();
	timeSinceLastFrame = gameTimeMs - lastFrameStartTimeMs;

	if (timeSinceLastFrame < frameDelayMs)
	{
		SDL_Delay(frameDelayMs - timeSinceLastFrame);
	}

	frameEndTimeMs = SDL_GetTicks();
	deltaTime = (frameEndTimeMs - lastFrameStartTimeMs)/1000.f;
	gameTime = frameEndTimeMs / 1000.f;
	lastFrameStartTimeMs = frameEndTimeMs;
	//std::cout << deltaTime << std::endl;
}

void Game::quit()
{
	isRunning = false;
}

void Game::cleanup()
{
	SDL_DestroyWindow(pWindow);
	SDL_DestroyRenderer(pRenderer);
	std::cout << "Goodbye World" << std::endl;
}
