#pragma once

#include "GameState.h"

class Game;

class Menu : public GameState {
public:
	Menu(Game* game);
	~Menu();

	void render();
	void update(float delta);

	bool handleEvent(SDL_Event* event);

	void changeTo();
	void changeFrom();

	void resize(int width, int height);
private:
	Game* game;
};

