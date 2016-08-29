#pragma once

#include "Entity.h"
#include "AssetManager.h"

class Sabertooth : public Entity {
public:
	Sabertooth(TileMap* map, AssetManager* am, float x, float y);
	~Sabertooth();

	void update(float delta);

	void bite();

	void collidedLeft();
	void collidedRight();
private:
	float time = 0, timeBetweenBites = 0.75f;
};

