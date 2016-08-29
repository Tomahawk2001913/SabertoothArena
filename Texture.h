#pragma once

#include <string>
#include <SDL.h>

class Texture {
public:
	Texture(SDL_Renderer* renderer, std::string path);
	~Texture();

	void render(float x, float y, float width, float height, double angle, SDL_RendererFlip flip = SDL_FLIP_NONE, SDL_Point* origin = NULL);
private:
	int width, height;

	SDL_Renderer* renderer;
	SDL_Texture* texture;

	bool load(SDL_Renderer* renderer, std::string path);
};

