#pragma once

#include <map>
#include <string>
#include <SDL.h>
#include <SDL_mixer.h>
#include "Texture.h"
#include "Animation.h"

class AssetManager {
public:
	AssetManager(SDL_Renderer* renderer);
	~AssetManager();

	enum IMAGES {
		GRASSTOPANDLEFT = 1, GRASSCENTER, GRASSTOPANDRIGHT, DIRT, REDBAR, PLAYER1, PLAYER2, SABERTOOTH1, SABERTOOTH2, WOODCLUBARM, SILVERCLUBARM, GOLDCLUBARM
	};

	enum ANIMATIONS {
		PLAYER, SABERTOOTH
	};

	Texture* getImage(IMAGES image);
	Animation* getAnimation(ANIMATIONS animation);
private:
	SDL_Renderer* renderer;
	std::map<IMAGES, Texture*> imageAssets;
	std::map<ANIMATIONS, Animation*> animations;

	Mix_Music* music;
};