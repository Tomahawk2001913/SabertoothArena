#include "Game.h"

#include <iostream>
#include <SDL_image.h>

Game::Game() {
	initSDL2();
	createWindowAndRenderer();

	am = new AssetManager(renderer);

	// Initialize gamestates.

	menuGameState = new Menu(this);
	playingGameState = new Playing(this);

	currentGameState = menuGameState;
}


Game::~Game() {
	destroyWindowAndRenderer();
	exitSDL2();

	delete menuGameState;
	menuGameState = NULL;
	delete playingGameState;
	playingGameState = NULL;

	delete am;
	am = NULL;
}

bool Game::loop() {
	// Calculate FPS somewhere here in the future?
	Uint32 startTicks = SDL_GetTicks();
	float delta = (startTicks - lastTick) / 1000.0f;
	lastTick = startTicks;

	if(delta < 0.0f) delta = 0.0f;
	if(delta > 0.1f) delta = 0.1f;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running = false;
		} else if (event.type == SDL_WINDOWEVENT) {
			switch (event.window.event) {
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				width = event.window.data1;
				height = event.window.data2;
				SDL_RenderPresent(renderer);
				break;
			case SDL_WINDOWEVENT_EXPOSED:
				SDL_RenderPresent(renderer);
				break;
			}
		} else currentGameState->handleEvent(&event);
	}

	SDL_RenderClear(renderer);

	if(currentGameState != NULL) {
		currentGameState->render();
		currentGameState->update(delta);
	}

	SDL_RenderPresent(renderer);

	return running;
}

void Game::switchGameState(GameState::GameStates gameState) {
	switch (gameState) {
	case GameState::MENU:
		currentGameState = menuGameState;
		break;
	case GameState::PLAYING:
		currentGameState = playingGameState;
		break;
	}
}

AssetManager* Game::getAssetManager() {
	return am;
}

int Game::getWidth() {
	return width;
}

int Game::getHeight() {
	return height;
}

// Private stuff

bool Game::initSDL2() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Error initializing SDL2: " << SDL_GetError() << std::endl;
		return false;
	} else if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		std::cout << "Error initializing SDL2 Image: " << IMG_GetError() << std::endl;
		return false;
	} else if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		std::cout << "Error opening audio: " << Mix_GetError() << std::endl;
		return false;
	}

	return true;
}

bool Game::exitSDL2() {
	Mix_CloseAudio();
	IMG_Quit();
	SDL_Quit();

	return true;
}

bool Game::createWindowAndRenderer() {
	window = SDL_CreateWindow("Sabertooth Arena - A Ludum Dare 36 Submission by Tomahawk2001913", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if (window == NULL) {
		std::cout << "Error initializing window: " << SDL_GetError() << std::endl;
	} else {
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (renderer == NULL) {
			std::cout << "Error initializing renderer: " << SDL_GetError() << std::endl;
		} else {
			SDL_SetRenderDrawColor(renderer, 0, 0xBF, 0xFF, 0);
		}
	}

	return true;
}

bool Game::destroyWindowAndRenderer() {
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	return true;
}
