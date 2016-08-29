#pragma once

#include <SDL.h>
#include "Entity.h"
#include "AssetManager.h"

class Player : public Entity {
public:
	Player(TileMap* map, AssetManager* am, float x, float y, float width, float height);
	~Player();

	void render(Camera* camera);
	void update(float delta);

	void addKill();

	void respawn();

	bool shouldClear() {return false;}

	bool handleEvent(SDL_Event* event);
private:
	Texture* healthBarTexture = NULL;

	float originalHealth = health;

	int kills = 0;

	bool goLeft = false, goRight = false;
};

