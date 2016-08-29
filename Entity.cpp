#include "Entity.h"

#include <iostream>
#include "TileMap.h"

Entity::Entity(TileMap* map, Animation* animation, float x, float y, float width, float height) {
	this->map = map;
	this->animation = animation;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	weapon = NULL;
}

Entity::~Entity() {

}

void Entity::render(Camera* camera) {
	if(animation == NULL) return;
	if (flipped) animation->getFrame(SDL_GetTicks() / 1000.0f)->render(x - camera->getX(), y - camera->getY(), width, height, 0, SDL_FLIP_HORIZONTAL);
	else animation->getFrame(SDL_GetTicks() / 1000.0f)->render(x - camera->getX(), y - camera->getY(), width, height, 0);

	if(weapon != NULL) {
		weapon->render(camera);
	}
}

void Entity::updatePosition(float delta) {
	float nX = x + xv * delta;
	float nY = y + yv * delta;

	xv += xa * delta;
	yv += ya * delta;
	
	ya += GRAVITY * delta;

	if(xv > 0) flipped = false;
	if(xv < 0) flipped = true;

	Rectangle bounds = {x, y, width, height};
	Rectangle test = {nX, nY, width, height};
	Rectangle yTest = {x, nY, width, height};
	Rectangle xTest = {nX, y, width, height};

	for (int lx = nX / TILE_SIZE - 3; lx < nX / TILE_SIZE + 3; ++lx) {
		for (int ly = nY / TILE_SIZE - 3; ly < nY / TILE_SIZE + 3; ++ly) {
			AssetManager::IMAGES tile = map->getTile(lx, ly);
			Rectangle tileBounds = {lx * TILE_SIZE, ly * TILE_SIZE, TILE_SIZE, TILE_SIZE};

			if (((int) tile) > 0 && intersects(test, tileBounds)) {
				if (intersects(tileBounds, yTest)) {
					if (topCollision(bounds, test, tileBounds)) {
						nY = tileBounds.y + tileBounds.height;
						yv = 0;
						if(ya < 0) ya = 0;
					}
					else if (bottomCollision(bounds, test, tileBounds)) {
						nY = tileBounds.y - height;
						yv = 0;
						if(ya > 0) ya = 0;
						touchingGround = true;
					}
				}

				if (intersects(tileBounds, xTest)) {
					if (leftCollision(bounds, test, tileBounds)) {
						nX = tileBounds.x + tileBounds.width;
						collidedLeft();
					}
					else if (rightCollision(bounds, test, tileBounds)) {
						nX = tileBounds.x - width;
						collidedRight();
					}
				}
			}
		}
	}

	//if(yv > 0) touchingGround = false;

	x = nX;
	y = nY;
}

bool Entity::intersects(Rectangle& test1, Rectangle& test2) {
	if(test1.x >= test2.x + test2.width || test1.x + test1.width <= test2.x) return false;
	if(test1.y >= test2.y + test2.height || test1.y + test1.height <= test2.y) return false;

	return true;
}

void Entity::damage(float amount) {
	health -= amount;
}

float Entity::getX() {
	return x;
}

float Entity::getY() {
	return y;
}

float Entity::getWidth() {
	return width;
}

float Entity::getHeight() {
	return height;
}

bool Entity::isFlipped() {
	return flipped;
}

TileMap* Entity::getTileMap() {
	return map;
}

// Private stuff.

bool Entity::topCollision(Rectangle& original, Rectangle& intersect, Rectangle& intersected) {
	if(original.y < intersected.y + intersected.height) return false;
	if(intersect.y < intersected.y + intersected.height) return true;
	return false;
}

bool Entity::bottomCollision(Rectangle& original, Rectangle& intersect, Rectangle& intersected) {
	if (original.y + original.height > intersected.y) return false;
	if (intersect.y + intersect.height > intersect.y) return true;
	return false;
}

bool Entity::leftCollision(Rectangle& original, Rectangle& intersect, Rectangle& intersected) {
	if (original.x < intersected.x + intersected.width) return false;
	if (intersect.x < intersected.x + intersected.width) return true;
	return false;
}

bool Entity::rightCollision(Rectangle& original, Rectangle& intersect, Rectangle& intersected) {
	if (original.x + original.width > intersected.x) return false;
	if (intersect.x + original.width > intersected.x) return true;
	return false;
}