#include "Texture.h"

#include <iostream>
#include <SDL_image.h>

Texture::Texture(SDL_Renderer* renderer, std::string path) {
	this->renderer = renderer;
	load(renderer, path);
}

Texture::~Texture() {
	SDL_DestroyTexture(texture);
	texture = NULL;
}

void Texture::render(float x, float y, float width, float height, double angle, SDL_RendererFlip flip, SDL_Point* origin) {
	SDL_Rect rect = { (int) x, (int) y, (int) width, (int) height };

	SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, origin, flip);
}

// Private stuff

bool Texture::load(SDL_Renderer* renderer, std::string path) {
	SDL_Surface* tempSurface = IMG_Load(path.c_str());

	if (tempSurface == NULL) {
		std::cout << "Error loading image: " << IMG_GetError() << std::endl;
		return false;
	} else {
		texture = SDL_CreateTextureFromSurface(renderer, tempSurface);

		if (texture == NULL) {
			std::cout << "Error creating texture: " << SDL_GetError() << std::endl;
			SDL_FreeSurface(tempSurface);
			return false;
		} else {
			width = tempSurface->w;
			height = tempSurface->h;

			SDL_FreeSurface(tempSurface);
		}
	}

	return true;
}

