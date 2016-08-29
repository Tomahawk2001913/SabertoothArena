#include "Spawner.h"

#include <iostream>
#include "TileMap.h"
#include "Sabertooth.h"

Spawner::Spawner(TileMap* map, AssetManager* am, float x, float y, float timeBetweenSpawns) : Entity(map, NULL, x, y, 0, 0) {
	this->am = am;
	this->timeBetweenSpawns = timeBetweenSpawns;
}

Spawner::~Spawner() {

}

void Spawner::render(Camera* camera) {
	
}

void Spawner::update(float delta) {
	timeSinceSpawn += delta;

	if (timeSinceSpawn >= timeBetweenSpawns) {
		timeSinceSpawn -= timeBetweenSpawns;
		map->addEntity(new Sabertooth(map, am, x, y));
	}
}