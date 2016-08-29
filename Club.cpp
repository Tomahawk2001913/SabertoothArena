#include "Club.h"

#include <iostream>
#include "Entity.h"
#include "TileMap.h"

Club::Club(AssetManager* am, Entity* entity, SDL_Point relativePosition, CLUB_TYPE type) : Weapon(am->getImage(AssetManager::WOODCLUBARM), entity, relativePosition) {
	this->am = am;
	angle = 25;

	changeType(WOOD);
}

Club::~Club() {

}

void Club::changeType(CLUB_TYPE type) {
	switch (type) {
	case WOOD:
		texture = am->getImage(AssetManager::WOODCLUBARM);
		damage = 20.0f;
		break;
	case SILVER:
		texture = am->getImage(AssetManager::SILVERCLUBARM);
		damage = 50.0f;
		break;
	case GOLD:
		texture = am->getImage(AssetManager::GOLDCLUBARM);
		damage = 100.0f;
		break;
	}
}

void Club::use() {
	if(!used) {
		angle = 0;
		
		Entity::Rectangle bounds;

		if (parent->isFlipped()) bounds = { -relativePosition.x + parent->getX(), -relativePosition.y + parent->getY(), width, height };
		else bounds = { relativePosition.x + parent->getX(), relativePosition.y + parent->getY(), width, height };

		for (unsigned int i = 0; i < parent->getTileMap()->getEntities()->size(); ++i) {
			Entity* entity = (*parent->getTileMap()->getEntities())[i];
			if (entity != parent && entity->intersects(bounds, Entity::Rectangle {entity->getX(), entity->getY(), entity->getWidth(), entity->getHeight()})) {
				entity->damage(damage);
				return;
			}
		}
	}
}

void Club::unuse() {
	angle = 25;
	used = false;
}
