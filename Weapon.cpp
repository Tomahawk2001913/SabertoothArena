#include "Weapon.h"

#include "Entity.h"

Weapon::Weapon(Texture* texture, Entity* entity, SDL_Point relativePosition) {
	this->texture = texture;
	parent = entity;
	this->relativePosition = relativePosition;
}

Weapon::~Weapon() {

}

void Weapon::render(Camera* camera) {
	SDL_Point origin = { 19, height / 2 };

	if(parent->isFlipped()) {
		texture->render(relativePosition.x + parent->getX() - camera->getX(), relativePosition.y + parent->getY() - camera->getY(), width, height, 180 + angle, SDL_FLIP_VERTICAL, &origin);
	} else {
		texture->render(relativePosition.x + parent->getX() - camera->getX(), relativePosition.y + parent->getY() - camera->getY(), width, height, -angle, SDL_FLIP_NONE, &origin);
	}
}
