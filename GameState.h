#pragma once

#include <SDL.h>

class GameState {
public:
	GameState();
	virtual ~GameState();

	virtual void render() = 0;
	virtual void update(float delta) = 0;

	virtual bool handleEvent(SDL_Event* event) = 0;

	virtual void changeTo() = 0;
	virtual void changeFrom() = 0;

	virtual void resize(int width, int height) = 0;

	enum GameStates {
		MENU, PLAYING
	};
};

