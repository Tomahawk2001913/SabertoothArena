#include "AssetManager.h"

#include <iostream>
#include <vector>

AssetManager::AssetManager(SDL_Renderer* renderer) {
	this->renderer = renderer;
	
	std::cout << "Loading assets..." << std::endl;

	// Misc
	imageAssets[REDBAR] = new Texture(renderer, "assets/images/redbar.png");

	// Player
	imageAssets[PLAYER1] = new Texture(renderer, "assets/images/entities/caveman1.png");
	imageAssets[PLAYER2] = new Texture(renderer, "assets/images/entities/caveman2.png");

	// Weapons
	imageAssets[WOODCLUBARM] = new Texture(renderer, "assets/images/weapons/woodclubarm.png");
	imageAssets[SILVERCLUBARM] = new Texture(renderer, "assets/images/weapons/silverclubarm.png");
	imageAssets[GOLDCLUBARM] = new Texture(renderer, "assets/images/weapons/goldclubarm.png");

	// Enemies
	imageAssets[SABERTOOTH1] = new Texture(renderer, "assets/images/entities/sabertooth1.png");
	imageAssets[SABERTOOTH2] = new Texture(renderer, "assets/images/entities/sabertooth2.png");

	// Tiles
	imageAssets[GRASSTOPANDLEFT] = new Texture(renderer, "assets/images/tiles/grasstopandleft.png");
	imageAssets[GRASSCENTER] = new Texture(renderer, "assets/images/tiles/grasscenter.png");
	imageAssets[GRASSTOPANDRIGHT] = new Texture(renderer, "assets/images/tiles/grasstopandright.png");

	imageAssets[DIRT] = new Texture(renderer, "assets/images/tiles/dirt.png");

	// Animations
	std::vector<Texture*> *playerFrames = new std::vector<Texture*> {imageAssets[PLAYER1], imageAssets[PLAYER2]}, 
						  *sabertoothFrames = new std::vector<Texture*> {imageAssets[SABERTOOTH1], imageAssets[SABERTOOTH2]};

	animations[PLAYER] = new Animation(playerFrames, 0.25f, Animation::FORWARD);
	animations[SABERTOOTH] = new Animation(sabertoothFrames, 0.25f, Animation::FORWARD);

	music = Mix_LoadMUS("assets/music/Sabertooth_Arena_Theme.mp3");

	std::cout << "Done loading assets." << std::endl;

	std::cout << "Starting music..." << std::endl;

	Mix_PlayMusic(music, -1);

	std::cout << "Done starting music." << std::endl;
}


AssetManager::~AssetManager() {
	std::cout << "Stopping music..." << std::endl;

	Mix_PauseMusic();

	std::cout << "Stopped music." << std::endl;

	std::cout << "Unloading assets..." << std::endl;

	Mix_FreeMusic(music);

	for (std::map<IMAGES, Texture*>::iterator i = imageAssets.begin(); i != imageAssets.end(); ++i) {
		delete i->second;
		imageAssets[i->first] = NULL;
	}

	for (std::map<ANIMATIONS, Animation*>::iterator i = animations.begin(); i != animations.end(); ++i) {
		delete i->second;
		animations[i->first] = NULL;
	}

	std::cout << "Done unloading assets." << std::endl;
}

Texture* AssetManager::getImage(IMAGES image) {
	return imageAssets[image];
}

Animation* AssetManager::getAnimation(ANIMATIONS animation) {
	return animations[animation];
}