#include "Sabertooth.h"

#include <iostream>
#include "TileMap.h"

Sabertooth::Sabertooth(TileMap* map, AssetManager* am, float x, float y) : Entity(map, am->getAnimation(AssetManager::SABERTOOTH), x, y, 152, 70) {
	if(SDL_GetTicks() % 2 < 5) xv = 250;
	else xv = -250;
}

Sabertooth::~Sabertooth() {

}

void Sabertooth::update(float delta) {
	time += delta;

	updatePosition(delta);
	if(health <= 0) {
		map->removeEntity(this);
		map->getPlayer()->addKill();
	}

	if (time >= timeBetweenBites) {
		bite();
		time -= timeBetweenBites;
	}
}

void Sabertooth::bite() {
	Rectangle bounds, playerBounds = { map->getPlayer()->getX(), map->getPlayer()->getY(), map->getPlayer()->getWidth(), map->getPlayer()->getHeight() };

	if(isFlipped()) bounds = { x, y, width * 0.2f, height };
	else bounds = { x + width - width * 0.2f, y, width * 0.2f, height };

	if(intersects(bounds, playerBounds)) map->getPlayer()->damage(8.0f);
}

void Sabertooth::collidedLeft() {
	xv = -xv;
}

void Sabertooth::collidedRight() {
	xv = -xv;
}