#pragma once

#include <SDL.h>
#include <string>
#include <vector>
#include "AssetManager.h"
#include "Camera.h"
#include "Player.h"

#define TILE_SIZE 128
#define GRAVITY 700.0f

class Game;

class TileMap {
public:
	TileMap(Game* game, AssetManager* am, std::string path);
	~TileMap();

	void render(Camera* camera);
	void update(float delta);

	void addEntity(Entity* entity);
	void removeEntity(Entity* entity);

	void handleEvent(SDL_Event* event);

	Game* getGame();

	AssetManager::IMAGES getTile(int x, int y);

	SDL_Point getSpawnPoint();

	std::vector<Entity*>* getEntities();
	Player* getPlayer();
private:
	Game* game;
	Player* player;
	AssetManager* am;

	AssetManager::IMAGES* tiles;
	std::vector<Entity*> entities;
	std::vector<Entity*> deadEntities;
	std::vector<Entity*> addEntities;

	SDL_Point spawnPoint = {0, 0};

	int width, height;

	void load(std::string path);
};

