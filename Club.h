#pragma once

#include "Weapon.h"
#include "AssetManager.h"

class Club : public Weapon {
public:
	enum CLUB_TYPE {
		WOOD, SILVER, GOLD
	};

	Club(AssetManager* am, Entity* entity, SDL_Point relativePosition, CLUB_TYPE type = WOOD);
	~Club();

	void changeType(CLUB_TYPE type);

	void use();
	void unuse();
private:
	AssetManager* am;
	CLUB_TYPE type;

	float damage = 20.0f;
};

