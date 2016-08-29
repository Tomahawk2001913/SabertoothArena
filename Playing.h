#pragma once

#include "GameState.h"
#include "TileMap.h"
#include "Camera.h"

class Game;

class Playing : public GameState {
public:
	Playing(Game* game);
	~Playing();

	void render();
	void update(float delta);

	bool handleEvent(SDL_Event* event);

	void changeTo();
	void changeFrom();

	void resize(int width, int height);
private:
	Game* game;
	TileMap* map;
	Camera* camera;
};

