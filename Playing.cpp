#include "Playing.h"

#include <iostream>
#include "Game.h"

Playing::Playing(Game* game) {
	this->game = game;
	map = new TileMap(game, game->getAssetManager(), "assets/maps/example.numbermap");
	camera = new Camera(0, 0, game->getWidth(), game->getHeight());
}


Playing::~Playing() {
	delete map;
	map = NULL;

	delete camera;
	camera = NULL;
}

void Playing::render() {
	map->render(camera);
}

void Playing::update(float delta) {
	map->update(delta);
}

bool Playing::handleEvent(SDL_Event* event) {
	map->handleEvent(event);
	return true;
}

void Playing::changeTo() {

}

void Playing::changeFrom() {

}

void Playing::resize(int width, int height) {
	camera->resize(width, height);
}