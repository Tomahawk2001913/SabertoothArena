#pragma once

#include <SDL.h>
#include "Texture.h"
#include "Camera.h"

class Entity;

class Weapon {
public:
	Weapon(Texture* texture, Entity* parent, SDL_Point relativePosition);
	virtual ~Weapon();

	void render(Camera* camera);

	virtual void use() = 0;
	virtual void unuse() = 0;
protected:
	float width = 128 * 0.75f, height = 96 * 0.75f, angle = 0;

	bool used = false;

	Entity* parent;
	SDL_Point relativePosition;
	Texture* texture;
};

