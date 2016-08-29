#include "TileMap.h"

#include <iostream>
#include <fstream>
#include "Spawner.h"

class Game;

TileMap::TileMap(Game* game, AssetManager* am, std::string path) {
	this->game = game;
	this->am = am;
	load(path);
	player = new Player(this, am, spawnPoint.x, spawnPoint.y, 80, 128);
	entities.push_back(player);
}

TileMap::~TileMap() {
	delete player;
	player = NULL;

	delete tiles;
}

void TileMap::render(Camera* camera) {
	// Render entities.
	camera->lookAt(player->getX() + player->getWidth() / 2, player->getY());
	for (unsigned int i = 0; i < entities.size(); ++i) {
		entities[i]->render(camera);
	}

	// Render terrain.
	for (int i = 0; i < width * height; ++i) {
		if((int) am->getImage(tiles[i]) <= 0) continue;
		am->getImage(tiles[i])->render(i % width * TILE_SIZE - camera->getX(), i / width * TILE_SIZE - camera->getY(), TILE_SIZE, TILE_SIZE, 0);
	}
}

void TileMap::update(float delta) {
	for (unsigned int i = 0; i < entities.size(); ++i) {
		entities[i]->update(delta);
	}

	for (unsigned int i = 0; i < deadEntities.size(); ++i) {
		entities.erase(std::find(entities.begin(), entities.end(), deadEntities[i]));
	}

	deadEntities.clear();

	for (unsigned int i = 0; i < addEntities.size(); ++i) {
		entities.push_back(addEntities[i]);
	}

	addEntities.clear();
}

void TileMap::addEntity(Entity* entity) {
	addEntities.push_back(entity);
}

void TileMap::removeEntity(Entity* entity) {
	deadEntities.push_back(entity);
}

void TileMap::handleEvent(SDL_Event* event) {
	player->handleEvent(event);
}

Game* TileMap::getGame() {
	return game;
}

AssetManager::IMAGES TileMap::getTile(int x, int y) {
	if (x >= 0 && x < width && y >= 0 && y < height) {
		return tiles[y * width + x];
	}

	return (AssetManager::IMAGES) 0;
}

SDL_Point TileMap::getSpawnPoint() {
	return spawnPoint;
}

std::vector<Entity*>* TileMap::getEntities() {
	return &entities;
}

Player* TileMap::getPlayer() {
	return player;
}

// Private stuff

void TileMap::load(std::string path) {
	width = 0;
	height = 0;

	std::ifstream file(path);

	if (!file.is_open()) {
		std::cout << "Failed to load map from: " << path.c_str() << std::endl;
		return;
	}

	int x = 0, y = 0, total;

	file >> width;
	if(file.fail()) std::cout << "Error finding map width." << std::endl;
	file >> height;
	if(file.fail()) std::cout << "Error finding map height." << std::endl;

	total = width * height;

	tiles = new AssetManager::IMAGES[total];

	for (int i = 0; i < total; ++i) {
		int type = 0;
		file >> type;

		if (file.fail()) {
			std::cout << "Error loading tiles at index: " << i << " at path: " << path.c_str() << std::endl;
			continue;
		}

		if(type > 0) tiles[i] = (AssetManager::IMAGES) type;
		else switch (type) {
		case -1:
			spawnPoint = { (i % width) * TILE_SIZE, i / width * TILE_SIZE };
			break;
		case -2:
			addEntity(new Spawner(this, am, i % width * TILE_SIZE, i / width * TILE_SIZE, 2.5f));
		}
		
	}
}
