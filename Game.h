#pragma once

#include <SDL.h>
#include "AssetManager.h"
#include "GameState.h"
#include "Menu.h"
#include "Playing.h"

class Game {
public:
	Game();
	~Game();

	bool loop();

	void switchGameState(GameState::GameStates);

	AssetManager* getAssetManager();

	int getWidth();
	int getHeight();
private:
	bool running = true;

	int width = 960, height = 540;

	Uint32 lastTick = 0;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
	AssetManager* am;
	GameState* currentGameState;

	// Gamestates
	Menu* menuGameState;
	Playing* playingGameState;

	bool initSDL2();
	bool exitSDL2();

	bool createWindowAndRenderer();
	bool destroyWindowAndRenderer();
};