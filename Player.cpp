#include "Player.h"

#include "Club.h"
#include "TileMap.h"
#include "Game.h"
#include "Spawner.h"

Player::Player(TileMap* map, AssetManager* am, float x, float y, float width, float height) : Entity(map, am->getAnimation(AssetManager::PLAYER), x, y, width, height) {
	healthBarTexture = am->getImage(AssetManager::REDBAR);
	speed = 300;
	weapon = new Club(am, this, SDL_Point {PLAYER_WEAPON_X, PLAYER_WEAPON_Y}, Club::WOOD);
}

Player::~Player() {

}

void Player::render(Camera* camera) {
	Entity::render(camera);

	healthBarTexture->render(0, 0, map->getGame()->getWidth() * health / originalHealth, 25, 0);
}

void Player::update(float delta) {
	float xv = 0;
	
	if(goLeft) xv += -speed;
	if(goRight) xv += speed;

	this->xv += xv;

	updatePosition(delta);

	this->xv -= xv;

	if(health <= 0.0f) respawn();
}

void Player::addKill() {
	++kills;

	if (kills > 5) {
		((Club*) weapon)->changeType(Club::SILVER);
	} else ((Club*)weapon)->changeType(Club::WOOD);

	if (kills > 15) {
		((Club*)weapon)->changeType(Club::GOLD);
	}
}

void Player::respawn() {
	x = map->getSpawnPoint().x;
	y = map->getSpawnPoint().y;
	kills = 0;

	health = 100.0f;

	for (int i = 0; i < map->getEntities()->size(); ++i) {
		if((*map->getEntities())[i]->shouldClear()) map->removeEntity((*map->getEntities())[i]);
	}

	((Club*)weapon)->changeType(Club::WOOD);

	goLeft = goRight = false;
}

bool Player::handleEvent(SDL_Event* event) {
	if (event->type == SDL_KEYDOWN) {
		switch (event->key.keysym.sym) {
		case SDLK_a:
			goLeft = true;
			return true;
		case SDLK_d:
			goRight = true;
			return true;
		case SDLK_w:
		case SDLK_e:
			if (weapon != NULL) {
				weapon->use();

				return true;
			}

			return false;
		case SDLK_SPACE:
			if(touchingGround) {
				yv += -speed * 0.85f;
				touchingGround = false;
			}

			return true;
		default:
			break;
		}
	} else if (event->type == SDL_KEYUP) {
		switch (event->key.keysym.sym) {
		case SDLK_a:
			goLeft = false;
			return true;
		case SDLK_d:
			goRight = false;
			return true;
		case SDLK_w:
		case SDLK_e:
			if (weapon != NULL) {
				weapon->unuse();

				return true;
			}

			return false;
		default:
			break;
		}
	}
	return false;
}
