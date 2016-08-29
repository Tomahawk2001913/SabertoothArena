#pragma once

#include "Entity.h"
#include "AssetManager.h"

class Spawner : public Entity {
public:
	Spawner(TileMap* map, AssetManager* am, float x, float y, float timeBetweenSpawns = 3.5f);
	virtual ~Spawner();

	void render(Camera* camera);
	void update(float delta);

	bool shouldClear() {return false;}
private:
	AssetManager* am;
	float timeBetweenSpawns, timeSinceSpawn = 0;
};