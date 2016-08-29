#pragma once

#include "Camera.h"
#include "Animation.h"
#include "Weapon.h"

#define PLAYER_WEAPON_X 20
#define PLAYER_WEAPON_Y 5

class TileMap;

class Entity {
public:
	Entity(TileMap* map, Animation* animation, float x, float y, float width, float height);
	virtual ~Entity();

	struct Rectangle {
		float x, y, width, height;
	};

	virtual void render(Camera* camera);
	virtual void update(float delta) = 0;

	virtual void updatePosition(float delta);

	bool intersects(Rectangle& test1, Rectangle& test2);

	virtual bool shouldClear() { return true; }

	virtual void collidedLeft() {};
	virtual void collidedRight() {};

	virtual void damage(float amount);

	float getX();
	float getY();
	float getWidth();
	float getHeight();
	bool isFlipped();
	TileMap* getTileMap();
protected:
	float x = 0, y = 0, xv = 0, yv = 0, xa = 0, ya = 0, width = 0, height = 0, speed = 0, health = 100.0f;
	bool touchingGround = false, flipped = false;

	TileMap* map;
	Weapon* weapon;
private:
	Animation* animation;

	bool topCollision(Rectangle& original, Rectangle& intersect, Rectangle& intersected);
	bool bottomCollision(Rectangle& original, Rectangle& intersect, Rectangle& intersected);
	bool leftCollision(Rectangle& original, Rectangle& intersect, Rectangle& intersected);
	bool rightCollision(Rectangle& original, Rectangle& intersect, Rectangle& intersected);
};

