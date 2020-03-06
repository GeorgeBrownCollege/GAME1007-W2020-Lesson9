#include "Game.h"
#include <iostream>
#include <SDL_image.h>

void Game::moveShip()
{
	ship.setPosition(mousePosition.x, 500);
}

void Game::checkBounds()
{
	// check right boundary
	if(ship.getPosition().x > 800 - ship.getPosition().w)
	{
		
		ship.setPosition(800 - ship.getPosition().w * 0.5, 500);
	}

	// check left boundary
	if (ship.getPosition().x < 0)
	{

		ship.setPosition(ship.getPosition().w * 0.5, 420);
	}
}

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
	ship = Sprite(pRenderer, "ship.png", 73, 155);
	ship.setPosition(364, 420);



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
	auto wheel = 0;
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			// when the x button is clicked on the window
			case SDL_QUIT:
				quit();
				break;
			// when the mouse is moved
			case SDL_MOUSEMOTION:
				mousePosition.x = event.motion.x;
				mousePosition.y = event.motion.y;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					// press on the esc key to quit
					case SDLK_ESCAPE:
						quit();
					break;
					case SDLK_w:
						// move up
						std::cout << "move up" << std::endl;
						break;
					case SDLK_a:
						// move left
						std::cout << "move left" << std::endl;
						ship.setPosition(ship.getPosition().x - 20, 420);
						break;
					case SDLK_s:
						// move down
						std::cout << "move down" << std::endl;
						break;
					case SDLK_d:
						// move right
						std::cout << "move right" << std::endl;
						ship.setPosition(ship.getPosition().x + 20, 420);
						break;
				}
				break;
			default:
				break;
		}
		
	}
}

void Game::update()
{
	// moves ship with mouse movement
	//moveShip();
	checkBounds();
	
}

void Game::draw()
{
	SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
	SDL_RenderClear(pRenderer);
	
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
